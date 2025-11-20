#!/usr/bin/env bash
# -----------------------------------------------------------------------------
# cub3D evaluation helper
# Automates build, norminette, valgrind and parser edge-case runs.
# -----------------------------------------------------------------------------
set -uo pipefail

PROJECT_ROOT="$(cd -- "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
LOG_DIR="$PROJECT_ROOT/tests/logs"
mkdir -p "$LOG_DIR"
SUPPRESS_FILE="$PROJECT_ROOT/valgrind-suppress.supp"

# Colors
ESC="\033["
RESET="${ESC}0m"
BOLD="${ESC}1m"
GREEN="${ESC}32m"
RED="${ESC}31m"
YELLOW="${ESC}33m"
CYAN="${ESC}36m"
GRAY="${ESC}90m"

declare -a SUMMARY_PASS=()
declare -a SUMMARY_FAIL=()
declare -a SUMMARY_WARN=()

RUN_BUILD=1
RUN_NORM=1
RUN_VALGRIND=1
RUN_BIN=1
DEFAULT_TIMEOUT=8
FILTER=""

usage() {
	cat <<'EOF'
Usage: ./tests/run_tester.sh [options]

Options:
  --skip-build        Skip the "make re" phase.
  --skip-norm         Skip Norminette (make norminette).
  --skip-valgrind     Skip the bundled Valgrind scenario (make valgrind).
  --skip-binaries     Skip binary execution matrix (parser/error cases).
  --timeout <sec>     Override timeout (in seconds) for positive runs (default: 8).
  --filter <token>    Run only scenarios whose label contains <token>.
  --list              Print available binary scenarios and exit.
  --help              Show this message and exit.
EOF
}

while [ "$#" -gt 0 ]; do
	case "$1" in
		--skip-build) RUN_BUILD=0 ;;
		--skip-norm) RUN_NORM=0 ;;
		--skip-valgrind) RUN_VALGRIND=0 ;;
		--skip-binaries) RUN_BIN=0 ;;
		--timeout)
			shift
			if [ -z "${1-}" ]; then
				echo "Missing value for --timeout" >&2
				exit 1
			fi
			DEFAULT_TIMEOUT="$1"
			;;
		--filter)
			shift
			FILTER="${1-}"
			;;
		--list)
			echo "Available binary scenarios:"
			list_scenarios=1
			;;
		--help)
			usage
			exit 0
			;;
		*)
			echo "Unknown option: $1" >&2
			usage
			exit 1
			;;
	esac
	shift || true
	if [ "${list_scenarios-0}" -eq 1 ]; then
		break
	fi
done

function print_section() {
	echo -e "\n${CYAN}${BOLD}==> $1${RESET}"
}

function record_result() {
	local label="$1"
	local status="$2"
	local note="${3-}"
	case "$status" in
		pass)
			SUMMARY_PASS+=("$label")
			printf "%b✔%b %s" "$GREEN" "$RESET" "$label"
			;;
		warn)
			SUMMARY_WARN+=("$label${note:+ ($note)}")
			printf "%b⚠%b %s" "$YELLOW" "$RESET" "$label"
			;;
		fail)
			SUMMARY_FAIL+=("$label${note:+ ($note)}")
			printf "%b✖%b %s" "$RED" "$RESET" "$label"
			;;
	esac
	if [ -n "$note" ]; then
		printf " %s" "$note"
	fi
	printf "\n"
}

function run_command() {
	local label="$1"
	local logfile="$2"
	shift 2
	local cmd=("$@")
	print_section "$label"
	(
		cd "$PROJECT_ROOT"
		"${cmd[@]}"
	) >"$logfile" 2>&1
	local status=$?
	if [ $status -eq 0 ]; then
		record_result "$label" pass "(log: ${logfile#$PROJECT_ROOT/})"
	else
		record_result "$label" fail "exit $status (see ${logfile#$PROJECT_ROOT/})"
	fi
}

function should_skip_scenario() {
	local label="$1"
	if [ -n "$FILTER" ] && [[ "$label" != *"$FILTER"* ]]; then
		return 0
	fi
	return 1
}

function run_binary_test() {
	local label="$1"
	local expectation="$2"
	local timeout="$3"
	local cmd_string="$4"
	if should_skip_scenario "$label"; then
		return
	fi
	local logfile="$LOG_DIR/${label}.log"
	print_section "Scenario: $label"
	local status
	if [ "$timeout" -gt 0 ]; then
		(
			cd "$PROJECT_ROOT"
			timeout "$timeout"s bash -c "$cmd_string"
		) >"$logfile" 2>&1
		status=$?
		if [ $status -eq 124 ]; then
			note="timeout ${timeout}s"
			status=0
		else
			note=""
		fi
	else
		(
			cd "$PROJECT_ROOT"
			bash -c "$cmd_string"
		) >"$logfile" 2>&1
		status=$?
		note=""
	fi
	case "$expectation" in
		success)
			if [ $status -eq 0 ]; then
				record_result "$label" pass "${note:+$note, }log: ${logfile#$PROJECT_ROOT/}"
			else
				record_result "$label" fail "exit $status (see ${logfile#$PROJECT_ROOT/})"
			fi
			;;
		error)
			if [ $status -eq 0 ]; then
				record_result "$label" fail "expected error, got exit 0"
			else
				record_result "$label" pass "detected error (log: ${logfile#$PROJECT_ROOT/})"
			fi
			;;
		*)
			record_result "$label" warn "unknown expectation"
			;;
	esac
}

POSITIVE_TESTS=(
	"mandatory:::success:::${DEFAULT_TIMEOUT}:::./cub3d assets/maps/mandatory.cub"
	"valid-small:::success:::${DEFAULT_TIMEOUT}:::./cub3d tests/maps/valid_small.cub"
)

NEGATIVE_TESTS=(
	"no-args:::error:::0:::./cub3d"
	"extra-args:::error:::0:::./cub3d assets/maps/mandatory.cub unexpected"
	"missing-texture:::error:::0:::./cub3d tests/maps/missing_texture.cub"
	"duplicate-identifier:::error:::0:::./cub3d tests/maps/duplicate_identifier.cub"
	"invalid-rgb:::error:::0:::./cub3d tests/maps/invalid_rgb.cub"
	"open-map:::error:::0:::./cub3d tests/maps/open_map.cub"
	"multiple-players:::error:::0:::./cub3d tests/maps/multiple_players.cub"
	"unknown-symbol:::error:::0:::./cub3d tests/maps/unknown_symbol.cub"
	"missing-map:::error:::0:::./cub3d tests/maps/missing_map.cub"
	"missing-asset:::error:::0:::./cub3d tests/maps/missing_asset.cub"
	"invalid-extension:::error:::0:::./cub3d tests/maps/invalid_extension.txt"
)

if [ "${list_scenarios-0}" -eq 1 ]; then
	for entry in "${POSITIVE_TESTS[@]}" "${NEGATIVE_TESTS[@]}"; do
		IFS=":::" read -r label _ <<< "$entry"
		echo " - $label"
	done
	exit 0
fi

print_section "Preparation"
if ! command -v timeout >/dev/null 2>&1; then
	record_result "timeout" warn "utility not found, success tests may hang"
fi

if [ $RUN_BUILD -eq 1 ]; then
	run_command "Build (make re)" "$LOG_DIR/build.log" make re
else
	record_result "Build" warn "skipped"
fi

if [ $RUN_NORM -eq 1 ]; then
	run_command "Norminette" "$LOG_DIR/norminette.log" make norminette
else
	record_result "Norminette" warn "skipped"
fi

if [ $RUN_VALGRIND -eq 1 ]; then
	run_command "Valgrind scenario" "$LOG_DIR/valgrind.log" make valgrind
	if [ -f "$SUPPRESS_FILE" ]; then
		echo -e "${GRAY}Valgrind suppression list applied: ${SUPPRESS_FILE#$PROJECT_ROOT/} (entries there are ignored).${RESET}"
	fi
else
	record_result "Valgrind" warn "skipped"
fi

if [ $RUN_BIN -eq 1 ]; then
    echo "Running binary scenarios..."
    echo "Count POSITIVE: ${#POSITIVE_TESTS[@]}"
    echo "Count NEGATIVE: ${#NEGATIVE_TESTS[@]}"
	for entry in "${POSITIVE_TESTS[@]}"; do
		label="${entry%%:::*}"
		rest="${entry#*:::}"
		expect="${rest%%:::*}"
		rest="${rest#*:::}"
		timeout="${rest%%:::*}"
		cmd="${rest#*:::}"
		run_binary_test "$label" "$expect" "$timeout" "$cmd"
	done
	for entry in "${NEGATIVE_TESTS[@]}"; do
		label="${entry%%:::*}"
		rest="${entry#*:::}"
		expect="${rest%%:::*}"
		rest="${rest#*:::}"
		timeout="${rest%%:::*}"
		cmd="${rest#*:::}"
		run_binary_test "$label" "$expect" "$timeout" "$cmd"
	done
else
	record_result "Binary scenarios" warn "skipped"
fi

print_section "Summary"
echo -e "${GREEN}Passed:${RESET} ${#SUMMARY_PASS[@]}"
for entry in "${SUMMARY_PASS[@]}"; do
	echo -e "  ${GREEN}✔${RESET} $entry"
done

echo -e "${YELLOW}Warnings:${RESET} ${#SUMMARY_WARN[@]}"
for entry in "${SUMMARY_WARN[@]}"; do
	echo -e "  ${YELLOW}⚠${RESET} $entry"
done

echo -e "${RED}Failed:${RESET} ${#SUMMARY_FAIL[@]}"
for entry in "${SUMMARY_FAIL[@]}"; do
	echo -e "  ${RED}✖${RESET} $entry"
done

echo -e "${GRAY}Logs stored under tests/logs${RESET}"
