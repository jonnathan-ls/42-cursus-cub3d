# ✅ Checklist - Desenvolvimento cub3D

Planejamento de checklist para norteamento durante desenvolvimento do projeto.

## 🚀 PREPARAÇÃO E SETUP INICIAL

### 📁 1. Estrutura do Projeto
- [x] Criar diretório raiz do projeto
- [x] Criar subdiretório `sources/` para código fonte
- [x] Criar subdiretório `includes/` para headers
- [x] Criar subdiretório `libaries/` para bibliotecas
- [x] Criar subdiretório `libaries/libft/` para libft
- [x] Criar subdiretório `libaries/mlx42/` para minilibx
- [x] Criar subdiretório `maps/` para arquivos .cub de teste
- [x] Criar subdiretório `textures/` para arquivos de textura
- [x] Criar subdiretório `tests/` para testes unitários
- [x] Criar arquivo `.gitignore` com exclusões apropriadas
- [x] Inicializar repositório git
- [x] Criar README.md básico com instruções

### 🔧 2. Makefile e Configurações
- [x] Criar Makefile com variáveis CC, CFLAGS, NAME
- [x] Definir CFLAGS: `-Wall -Wextra -Werror`
- [x] Adicionar regra `$(NAME)` para compilação principal
- [x] Adicionar regra `all` que chama `$(NAME)`
- [x] Adicionar regra `clean` para limpar objetos
- [x] Adicionar regra `fclean` que chama clean e remove executável
- [x] Adicionar regra `re` que chama fclean e all
- [ ] Adicionar regra `bonus` para features extras
- [x] Configurar compilação da libft
- [x] Configurar linking com minilibx (-lmlx -lm -lX11 -lXext)
- [x] Testar compilação básica

### 📚 3. Headers Principais
- [x] Criar `include/cub3d.h` como header principal
- [x] Incluir bibliotecas padrão: `<unistd.h>`, `<stdlib.h>`, `<stdio.h>`
- [x] Incluir `<math.h>` para funções matemáticas
- [x] Incluir `<fcntl.h>` para file operations
- [x] Incluir minilibx headers
- [x] Incluir libft header se utilizada
- [x] Criar cabeçalho de constantes para uso no projeto

## 🏗️ ESTRUTURAS DE DADOS FUNDAMENTAIS

### 📊 4. Estrutura do Jogador
- [ ] Criar `typedef struct s_player`
- [ ] Adicionar campo `double x` (posição X no mundo)
- [ ] Adicionar campo `double y` (posição Y no mundo)
- [ ] Adicionar campo `double angle` (direção que está olhando)
- [ ] Adicionar campo `double fov` (field of view em radianos)
- [ ] Adicionar campo `double move_speed` (velocidade de movimento)
- [ ] Adicionar campo `double rot_speed` (velocidade de rotação)

### 🗺️ 5. Estrutura do Mapa
- [ ] Criar `typedef struct s_map`
- [ ] Adicionar campo `char **grid` (matriz 2D do mapa)
- [ ] Adicionar campo `int width` (largura do mapa)
- [ ] Adicionar campo `int height` (altura do mapa)
- [ ] Adicionar campo `char *north_texture` (caminho textura norte)
- [ ] Adicionar campo `char *south_texture` (caminho textura sul)
- [ ] Adicionar campo `char *west_texture` (caminho textura oeste)
- [ ] Adicionar campo `char *east_texture` (caminho textura leste)
- [ ] Adicionar campo `int floor_color` (cor do chão em hex)
- [ ] Adicionar campo `int ceiling_color` (cor do teto em hex)

### 🎨 6. Estrutura de Imagem
- [ ] Criar `typedef struct s_image`
- [ ] Adicionar campo `void *img` (ponteiro da imagem mlx)
- [ ] Adicionar campo `char *data` (array de dados da imagem)
- [ ] Adicionar campo `int bits_per_pixel` (bits por pixel)
- [ ] Adicionar campo `int line_length` (tamanho da linha)
- [ ] Adicionar campo `int endian` (endianness)
- [ ] Adicionar campo `int width` (largura da imagem)
- [ ] Adicionar campo `int height` (altura da imagem)

### 🖼️ 7. Estrutura de Textura
- [ ] Criar `typedef struct s_texture`
- [ ] Adicionar campo `t_image img` (dados da imagem)
- [ ] Adicionar campo `int width` (largura da textura)
- [ ] Adicionar campo `int height` (altura da textura)
- [ ] Adicionar campo `char *path` (caminho do arquivo)

### 🎮 8. Estrutura Principal do Jogo
- [ ] Criar `typedef struct s_game`
- [ ] Adicionar campo `void *mlx` (ponteiro mlx)
- [ ] Adicionar campo `void *window` (ponteiro da janela)
- [ ] Adicionar campo `t_image screen` (buffer da tela)
- [ ] Adicionar campo `t_player player` (dados do jogador)
- [ ] Adicionar campo `t_map map` (dados do mapa)
- [ ] Adicionar campo `t_texture textures[4]` (texturas das 4 direções)
- [ ] Adicionar campo `int keys[256]` (estado das teclas)

## 🧮 FUNÇÕES MATEMÁTICAS BÁSICAS

### 📐 9. Funções Trigonométricas
- [ ] Implementar `double deg_to_rad(double degrees)`
- [ ] Implementar `double rad_to_deg(double radians)`
- [ ] Implementar `double normalize_angle(double angle)` (manter entre 0 e 2π)
- [ ] Testar conversões com valores conhecidos
- [ ] Testar normalização de ângulos negativos e > 2π

### 📊 10. Funções de Vetores
- [ ] Implementar `double distance_between_points(double x1, double y1, double x2, double y2)`
- [ ] Implementar `void rotate_point(double *x, double *y, double angle)`
- [ ] Implementar `double dot_product(double x1, double y1, double x2, double y2)`
- [ ] Testar cálculo de distâncias
- [ ] Testar rotação de pontos

### ⚡ 11. Otimizações Matemáticas (Opcional)
- [ ] Criar tabela de lookup para sin: `double sin_table[360]`
- [ ] Criar tabela de lookup para cos: `double cos_table[360]`
- [ ] Implementar `void init_trig_tables()`
- [ ] Implementar `double fast_sin(double angle)` usando tabela
- [ ] Implementar `double fast_cos(double angle)` usando tabela
- [ ] Benchmarkar diferença de performance

## 📄 PARSING DE ARQUIVO .CUB

### 🔍 12. Funções Auxiliares de Parsing
- [ ] Implementar `int is_empty_line(char *line)`
- [ ] Implementar `char *trim_whitespace(char *str)`
- [ ] Implementar `char **split_line(char *line, char delimiter)`
- [ ] Implementar `int is_valid_color(char *color_str)` (formato R,G,B)
- [ ] Implementar `int rgb_to_int(int r, int g, int b)`
- [ ] Testar todas as funções auxiliares

### 📝 13. Parser de Elementos de Configuração
- [ ] Implementar `int parse_texture_line(char *line, t_map *map)`
- [ ] Validar identificadores NO, SO, WE, EA
- [ ] Verificar se arquivo de textura existe
- [ ] Implementar `int parse_color_line(char *line, t_map *map)`
- [ ] Validar identificadores F, C
- [ ] Validar valores RGB (0-255)
- [ ] Implementar `int is_config_complete(t_map *map)`

### 🗺️ 14. Parser de Mapa
- [ ] Implementar `int parse_map_line(char *line, t_map *map)`
- [ ] Validar caracteres permitidos: 0, 1, N, S, E, W, espaços
- [ ] Calcular dimensões do mapa dinamicamente
- [ ] Detectar posição inicial do jogador
- [ ] Converter direção inicial (N,S,E,W) para ângulo
- [ ] Substituir caractere de jogador por '0' no mapa

### 📖 15. Parser Principal
- [ ] Implementar `int parse_cub_file(char *filename, t_game *game)`
- [ ] Verificar extensão .cub do arquivo
- [ ] Abrir arquivo e verificar se existe
- [ ] Implementar máquina de estados (CONFIG -> MAP)
- [ ] Ler arquivo linha por linha com get_next_line
- [ ] Chamar parsers específicos para cada tipo de linha
- [ ] Fechar arquivo após parsing
- [ ] Validar se todos os elementos obrigatórios foram fornecidos

## ✅ VALIDAÇÃO DE MAPA

### 🔍 16. Validações Básicas
- [ ] Implementar `int validate_map_characters(t_map *map)`
- [ ] Verificar se há exatamente um jogador
- [ ] Verificar se há pelo menos uma parede
- [ ] Implementar `int validate_map_rectangular(t_map *map)`
- [ ] Preencher linhas menores com espaços para formar retângulo

### 🌊 17. Algoritmo Flood Fill
- [ ] Implementar `void flood_fill(char **map, int x, int y, char target, char replacement)`
- [ ] Implementar versão recursiva
- [ ] Implementar proteção contra stack overflow
- [ ] Implementar `int is_map_closed(t_map *map)`
- [ ] Fazer cópia do mapa para flood fill
- [ ] Iniciar flood fill na posição do jogador
- [ ] Verificar se "vazou" para bordas do mapa

### ✅ 18. Validação Completa
- [ ] Implementar `int validate_complete_map(t_map *map)`
- [ ] Chamar todas as validações individuais
- [ ] Implementar `int validate_textures_exist(t_map *map)`
- [ ] Verificar se todos os arquivos de textura existem
- [ ] Implementar messages de erro específicas para cada tipo de falha

## 🖼️ SISTEMA GRÁFICO - MINILIBX

### 🚀 19. Inicialização MLX
- [ ] Implementar `int init_mlx(t_game *game)`
- [ ] Chamar `mlx_init()` e verificar retorno
- [ ] Criar janela com `mlx_new_window()`
- [ ] Definir título da janela
- [ ] Implementar `void cleanup_mlx(t_game *game)`
- [ ] Testar abertura e fechamento da janela

### 🎨 20. Sistema de Imagens
- [ ] Implementar `int init_image(t_game *game, t_image *img, int width, int height)`
- [ ] Criar imagem com `mlx_new_image()`
- [ ] Obter endereço dos dados com `mlx_get_data_addr()`
- [ ] Implementar `void destroy_image(t_game *game, t_image *img)`
- [ ] Implementar `void put_pixel_to_image(t_image *img, int x, int y, int color)`
- [ ] Implementar verificação de bounds
- [ ] Testar colocação de pixels

### 📋 21. Carregamento de Texturas
- [ ] Implementar `int load_texture(t_game *game, t_texture *texture, char *path)`
- [ ] Usar `mlx_xpm_file_to_image()` para carregar
- [ ] Obter dados da textura com `mlx_get_data_addr()`
- [ ] Implementar `int get_texture_color(t_texture *texture, int x, int y)`
- [ ] Implementar verificação de bounds da textura
- [ ] Implementar `void load_all_textures(t_game *game)`
- [ ] Testar carregamento com texturas reais

### 🖥️ 22. Sistema de Display
- [ ] Implementar `void clear_image(t_image *img, int color)`
- [ ] Implementar `void display_image(t_game *game)`
- [ ] Usar `mlx_put_image_to_window()` para mostrar
- [ ] Implementar double buffering básico
- [ ] Testar limpeza e display de imagens

## 🔦 ALGORITMO DE RAY-CASTING

### 🎯 23. Ray-casting Básico
- [ ] Implementar `double cast_ray(t_game *game, double angle)`
- [ ] Calcular direção do raio: `dx = cos(angle)`, `dy = sin(angle)`
- [ ] Implementar loop de "caminhada" do raio
- [ ] Usar step pequeno (ex: 0.01) para precisão
- [ ] Detectar colisão com parede: `if (map[y][x] == '1')`
- [ ] Retornar distância euclidiana até a parede
- [ ] Testar com ângulos conhecidos

### ⚡ 24. Otimização DDA
- [ ] Criar `typedef struct s_dda` para dados do algoritmo
- [ ] Implementar `double cast_ray_dda(t_game *game, double angle)`
- [ ] Calcular `delta_dist_x` e `delta_dist_y`
- [ ] Implementar grid traversal otimizado
- [ ] Detectar se hit foi em parede vertical ou horizontal
- [ ] Calcular coordenada exata do hit
- [ ] Comparar performance com versão básica

### 🎨 25. Correção de Fish-eye
- [ ] Implementar `double fix_fisheye(double distance, double ray_angle, double player_angle)`
- [ ] Calcular: `corrected_distance = distance * cos(ray_angle - player_angle)`
- [ ] Aplicar correção em todos os raios
- [ ] Testar visualmente a diferença

### 📐 26. Projeção na Tela
- [ ] Implementar `int calculate_wall_height(double distance)`
- [ ] Fórmula: `wall_height = (int)(SCREEN_HEIGHT / distance)`
- [ ] Implementar `void get_wall_bounds(int wall_height, int *start, int *end)`
- [ ] Calcular onde desenhar parede na tela
- [ ] Implementar clipping para alturas muito grandes

## 🖼️ RENDERIZAÇÃO DE PAREDES COM TEXTURAS

### 🎨 27. Mapeamento de Texturas
- [ ] Implementar `int get_wall_texture_id(double hit_x, double hit_y, int hit_side)`
- [ ] Determinar qual face da parede foi atingida (N, S, E, W)
- [ ] Implementar `int calculate_texture_x(double hit_x, double hit_y, int hit_side)`
- [ ] Mapear coordenada de hit para coordenada X da textura
- [ ] Implementar `void draw_textured_wall_stripe(t_game *game, int screen_x, int wall_height, int texture_id, int texture_x)`

### 🖌️ 28. Renderização de Colunas
- [ ] Implementar `void render_wall_column(t_game *game, int x, double distance, double hit_x, double hit_y, int hit_side)`
- [ ] Calcular altura da parede na tela
- [ ] Determinar textura e coordenada X
- [ ] Loop para desenhar cada pixel da coluna
- [ ] Calcular coordenada Y da textura para cada pixel
- [ ] Aplicar shading baseado na distância

### 🌈 29. Sistema de Shading
- [ ] Implementar `int apply_shading(int color, double distance)`
- [ ] Escurecer cores baseado na distância
- [ ] Implementar diferentes shading para faces diferentes
- [ ] Faces Norte/Sul mais claras que Leste/Oeste
- [ ] Implementar `int darken_color(int color, double factor)`

## 🎨 RENDERIZAÇÃO DE CHÃO E TETO

### 🏠 30. Renderização de Chão e Teto
- [ ] Implementar `void draw_floor_and_ceiling(t_game *game)`
- [ ] Para cada pixel acima da parede: cor do teto
- [ ] Para cada pixel abaixo da parede: cor do chão
- [ ] Implementar `void draw_background(t_game *game)`
- [ ] Preencher toda a tela antes do ray-casting
- [ ] Otimizar usando fills de áreas grandes

### 🎨 31. Gradientes de Profundidade (Bonus)
- [ ] Implementar `int calculate_floor_ceiling_shade(int y, int screen_height)`
- [ ] Simular névoa atmosférica
- [ ] Partes mais distantes (centro) mais escuras
- [ ] Implementar `void draw_gradient_background(t_game *game)`

## ⌨️ SISTEMA DE EVENTOS E INPUT

### 🎮 32. Setup de Eventos
- [ ] Implementar `int setup_events(t_game *game)`
- [ ] Registrar hook para key press: `mlx_hook(win, 2, 1L<<0, key_press, game)`
- [ ] Registrar hook para key release: `mlx_hook(win, 3, 1L<<1, key_release, game)`
- [ ] Registrar hook para fechar janela: `mlx_hook(win, 17, 1L<<17, close_game, game)`
- [ ] Registrar hook para loop: `mlx_loop_hook(mlx, game_loop, game)`

### ⌨️ 33. Sistema de Input de Teclado
- [ ] Implementar `int key_press(int keycode, t_game *game)`
- [ ] Mapear teclas: W, A, S, D, setas, ESC
- [ ] Atualizar array `game->keys[keycode] = 1`
- [ ] Implementar `int key_release(int keycode, t_game *game)`
- [ ] Atualizar array `game->keys[keycode] = 0`
- [ ] Implementar tratamento imediato para ESC

### 🚶 34. Sistema de Movimento
- [ ] Implementar `void update_player_movement(t_game *game)`
- [ ] Verificar estado das teclas W, A, S, D
- [ ] Calcular nova posição baseada na direção atual
- [ ] W: `new_x += cos(angle) * speed`, `new_y += sin(angle) * speed`
- [ ] S: movimento contrário ao W
- [ ] A/D: movimento perpendicular (strafe)
- [ ] Implementar `void update_player_rotation(t_game *game)`
- [ ] Setas esquerda/direita alteram `player.angle`

### 🚧 35. Sistema de Colisão
- [ ] Implementar `int check_collision(t_game *game, double new_x, double new_y)`
- [ ] Verificar se nova posição é parede: `map[(int)new_y][(int)new_x] == '1'`
- [ ] Implementar collision box ao redor do jogador
- [ ] Verificar múltiplos pontos da collision box
- [ ] Implementar `int can_move_to(t_game *game, double x, double y)`
- [ ] Implementar sliding collision (movimento parcial)

## 🔄 GAME LOOP PRINCIPAL

### ⏱️ 36. Controle de Frame Rate
- [ ] Implementar `long get_current_time_ms()`
- [ ] Usar `gettimeofday()` ou similar
- [ ] Implementar `double calculate_delta_time(long last_time)`
- [ ] Target de 60 FPS (16.67ms por frame)
- [ ] Implementar sleep para manter frame rate

### 🔄 37. Loop Principal do Jogo
- [ ] Implementar `int game_loop(t_game *game)`
- [ ] Calcular delta time
- [ ] Atualizar movimento do jogador
- [ ] Limpar buffer da tela
- [ ] Renderizar chão e teto
- [ ] Executar ray-casting para todas as colunas
- [ ] Displayar buffer na tela
- [ ] Atualizar time stamp

### 🎯 38. Renderização Frame Completo
- [ ] Implementar `void render_frame(t_game *game)`
- [ ] Loop para cada coluna da tela (x = 0; x < SCREEN_WIDTH; x++)
- [ ] Calcular ângulo do raio para coluna atual
- [ ] Executar ray-casting
- [ ] Renderizar coluna de parede
- [ ] Implementar `double calculate_ray_angle(t_game *game, int screen_x)`

## 🐛 DEBUGGING E TESTES

### 🔍 39. Sistema de Debug Visual
- [ ] Implementar `void draw_debug_info(t_game *game)`
- [ ] Mostrar FPS na tela
- [ ] Mostrar posição do jogador
- [ ] Mostrar ângulo atual
- [ ] Implementar toggle para debug mode
- [ ] Implementar `void draw_minimap_debug(t_game *game)`

### 🧪 40. Testes Básicos
- [ ] Criar mapas de teste simples
- [ ] Testar parsing com arquivos inválidos
- [ ] Testar movimento em diferentes direções
- [ ] Testar colisão com paredes
- [ ] Testar ray-casting em ângulos extremos
- [ ] Verificar memory leaks com valgrind

### 📊 41. Performance Testing
- [ ] Medir FPS em mapas pequenos e grandes
- [ ] Profilear funções mais custosas
- [ ] Testar com diferentes resoluções de tela
- [ ] Otimizar gargalos identificados

## 🎁 FEATURES BONUS

### 🗺️ 42. Sistema de Minimap
- [ ] Implementar `void draw_minimap(t_game *game)`
- [ ] Desenhar grid do mapa em escala reduzida
- [ ] Mostrar posição do jogador como ponto
- [ ] Mostrar direção do jogador como linha
- [ ] Implementar `void draw_minimap_tile(t_game *game, int x, int y, int color)`
- [ ] Posicionar minimap em canto da tela

### 🚪 43. Sistema de Portas
- [ ] Adicionar suporte ao caractere 'D' no mapa
- [ ] Criar `typedef struct s_door` com estado e posição
- [ ] Implementar `void update_doors(t_game *game)`
- [ ] Animação de abertura/fechamento
- [ ] Implementar `int interact_with_door(t_game *game)`
- [ ] Tecla E para interagir com porta próxima
- [ ] Modificar ray-casting para considerar portas

### 🎭 44. Sistema de Sprites
- [ ] Criar `typedef struct s_sprite`
- [ ] Implementar `void load_sprite(t_game *game, t_sprite *sprite, char *path)`
- [ ] Implementar `void render_sprites(t_game *game)`
- [ ] Billboard rendering (sempre de frente)
- [ ] Z-buffering para ordem correta
- [ ] Scaling baseado na distância
- [ ] Sistema de animação por frames

### 🖱️ 45. Controle por Mouse
- [ ] Registrar hook de movimento do mouse: `mlx_hook(win, 6, 1L<<6, mouse_move, game)`
- [ ] Implementar `int mouse_move(int x, int y, t_game *game)`
- [ ] Converter movimento horizontal em rotação
- [ ] Implementar sensibilidade configurável
- [ ] Implementar mouse capture/release
- [ ] Sistema de suavização de movimento

## ✅ VALIDAÇÃO FINAL E CLEANUP

### 🧹 46. Gerenciamento de Memória
- [ ] Implementar `void free_map(t_map *map)`
- [ ] Liberar grid 2D do mapa
- [ ] Liberar strings de caminhos de texturas
- [ ] Implementar `void free_textures(t_game *game)`
- [ ] Implementar `void cleanup_game(t_game *game)`
- [ ] Destruir imagens MLX
- [ ] Destruir janela e contexto MLX

### 🔍 47. Verificações Finais
- [ ] Executar norminette em todos os arquivos
- [ ] Verificar memory leaks com valgrind
- [ ] Testar com mapas complexos
- [ ] Verificar funcionamento de ESC e X da janela
- [ ] Testar erro handling com arquivos inexistentes
- [ ] Verificar mensagens de erro apropriadas

### 📋 48. Validação de Requisitos
- [ ] Ray-casting funcional com texturas
- [ ] Movimento WASD funcionando
- [ ] Rotação com setas funcionando
- [ ] Cores de chão e teto configuráveis
- [ ] Parsing correto de arquivos .cub
- [ ] Validação robusta de mapas
- [ ] Tratamento de erros adequado
- [ ] Cleanup limpo na saída

### 📦 49. Entrega Final
- [ ] Compilação limpa sem warnings
- [ ] Executável funciona conforme esperado
- [ ] Documentação atualizada
- [ ] Mapas de exemplo incluídos
- [ ] Texturas de exemplo incluídas
- [ ] Arquivo author com login da 42
- [ ] Verificação final de todos os requisitos

## 🎯 CHECKLIST DE TESTE FINAL

### ✅ Testes Obrigatórios
- [ ] `make` compila sem erros
- [ ] `make clean` remove objetos
- [ ] `make fclean` remove tudo
- [ ] `make re` recompila tudo
- [ ] `./cub3D map.cub` executa corretamente
- [ ] ESC fecha o programa
- [ ] X da janela fecha o programa
- [ ] Movimento WASD funciona
- [ ] Rotação com setas funciona
- [ ] Diferentes texturas por face
- [ ] Cores de chão/teto aplicadas
- [ ] Erro com mapa inválido
- [ ] Erro com arquivo inexistente
- [ ] Erro com argumentos incorretos

### 🎁 Testes Bonus (se implementados)
- [ ] Wall collision impede movimento
- [ ] Minimap aparece e atualiza
- [ ] Portas abrem/fecham com E
- [ ] Sprites aparecem corretamente
- [ ] Mouse controla rotação
