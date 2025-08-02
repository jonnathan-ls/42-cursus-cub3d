# 📚 Guia de Desenvolvimento - cub3D Project

*Um roteiro para estudar os conceitos necessários para desenvolvimento do projeto*

---

## 🎯 Visão Geral do Projeto

### O que é Ray-casting? 🔍
**Ray-casting** é uma técnica de renderização 3D que simula a visão humana "lançando raios" de luz a partir do ponto de vista do jogador. Imagine que você está em um quarto escuro com uma lanterna - o ray-casting funciona como se você apontasse a lanterna em todas as direções para "ver" o ambiente ao redor.

### Por que Wolfenstein 3D foi revolucionário? 🕹️
- **Primeiro FPS da história** (1992)
- **Ilusão de 3D** usando apenas matemática 2D
- **Performance otimizada** para computadores da época
- **Base para jogos** como Doom, Quake, Duke Nukem 3D

---

## 📖 Índice de Estudos

1. [🧮 Matemática Fundamental](#-matemática-fundamental)
2. [🎨 Conceitos de Computação Gráfica](#-conceitos-de-computação-gráfica)
3. [⚙️ Programação em C - Conceitos Avançados](#️-programação-em-c---conceitos-avançados)
4. [📐 Ray-casting - Teoria e Implementação](#-ray-casting---teoria-e-implementação)
5. [🖼️ miniLibX - Biblioteca Gráfica](#️-minilibx---biblioteca-gráfica)
6. [🗺️ Parsing e Validação de Mapas](#️-parsing-e-validação-de-mapas)
7. [🎮 Controles e Eventos](#-controles-e-eventos)
8. [🔧 Otimização e Performance](#-otimização-e-performance)
9. [🎁 Features Bonus](#-features-bonus)
10. [🐛 Debug e Testes](#-debug-e-testes)

---

## 🧮 Matemática Fundamental

### 📊 Trigonometria Essencial

#### Conceitos Básicos
```
🔺 Triângulo Retângulo:
   - Seno (sin): oposto/hipotenusa
   - Cosseno (cos): adjacente/hipotenusa  
   - Tangente (tan): oposto/adjacente
```

#### Aplicações no Ray-casting
- **Cálculo de direções**: `cos(angle)` e `sin(angle)`
- **Rotação do jogador**: Atualizar direção baseada no ângulo
- **Projeção de raios**: Determinar coordenadas X e Y dos raios

#### Exercícios Práticos 💡
1. Calcule a posição X,Y de um ponto a 5 unidades de distancia em 45°
2. Implemente uma função que rotaciona um vetor 2D
3. Converta graus para radianos e vice-versa

### 📐 Geometria Analítica

#### Vetores 2D
```c
typedef struct s_vector {
    double x;
    double y;
} t_vector;

// Operações básicas
t_vector vector_add(t_vector a, t_vector b);
t_vector vector_multiply(t_vector v, double scalar);
double vector_magnitude(t_vector v);
```

#### Distâncias e Colisões
- **Distância Euclidiana**: `sqrt((x2-x1)² + (y2-y1)²)`
- **Detecção de colisão**: Verificar se um ponto está dentro de um quadrado
- **Interpolação linear**: Para movimento suave

---

## 🎨 Conceitos de Computação Gráfica

### 🖥️ Sistema de Coordenadas

#### Coordinate System Basics
```
Screen Coordinates (Pixels):
(0,0) -------- (WIDTH,0)
  |              |
  |    SCREEN    |
  |              |
(0,HEIGHT) -- (WIDTH,HEIGHT)

World Coordinates (Game Map):
  ^
  | Y
  |
  |
  +---------> X
(0,0)
```

#### Transformações de Coordenadas
- **World → Screen**: Converter posição do jogo para pixels na tela
- **Normalização**: Valores entre 0 e 1 para facilitar cálculos
- **Scaling**: Ajustar tamanho baseado na distância

### 🎨 Cores e Pixel Manipulation

#### Formato de Cores
```c
// RGB Format (32-bit)
typedef struct s_color {
    int r; // Red (0-255)
    int g; // Green (0-255)  
    int b; // Blue (0-255)
    int a; // Alpha (transparency)
} t_color;

// Hexadecimal: 0xAARRGGBB
int color_to_int(t_color color) {
    return (color.a << 24) | (color.r << 16) | (color.g << 8) | color.b;
}
```

#### Manipulação de Pixels
- **Shading**: Escurecer cores baseado na distância
- **Texture mapping**: Aplicar texturas nas paredes
- **Color interpolation**: Criar gradientes suaves

---

## ⚙️ Programação em C - Conceitos Avançados

### 🏗️ Estruturas de Dados Essenciais

#### Game State Structure
```c
typedef struct s_player {
    double x;           // Posição X do jogador
    double y;           // Posição Y do jogador
    double angle;       // Direção que o jogador está olhando
    double fov;         // Field of View (campo de visão)
} t_player;

typedef struct s_game {
    t_player player;
    char **map;         // Mapa 2D
    int map_width;
    int map_height;
    void *mlx;          // Ponteiro miniLibX
    void *window;       // Janela do jogo
    void *image;        // Buffer de imagem
} t_game;
```

#### Gerenciamento de Memória
```c
// Alocação segura
char **allocate_2d_array(int rows, int cols) {
    char **array = malloc(rows * sizeof(char*));
    if (!array) return NULL;
    
    for (int i = 0; i < rows; i++) {
        array[i] = malloc(cols * sizeof(char));
        if (!array[i]) {
            for (int j = 0; j < i; j++)
                free(array[j]);
            free(array);
            return NULL;
        }
    }
    return array;
}
```

### 🔍 Error Handling Robusto

#### Estratégias de Tratamento de Erro
```c
typedef enum e_error {
    ERROR_NONE = 0,
    ERROR_MALLOC,
    ERROR_FILE_NOT_FOUND,
    ERROR_INVALID_MAP,
    ERROR_MLX_INIT,
    ERROR_TEXTURE_LOAD
} t_error;

void handle_error(t_error error, char *context) {
    write(2, "Error\n", 6);
    if (context) {
        write(2, context, strlen(context));
        write(2, ": ", 2);
    }
    
    switch (error) {
        case ERROR_MALLOC:
            write(2, "Memory allocation failed\n", 25);
            break;
        case ERROR_FILE_NOT_FOUND:
            write(2, "File not found\n", 15);
            break;
        // ... outros casos
    }
    exit(1);
}
```

---

## 📐 Ray-casting - Teoria e Implementação

### 🔦 Conceito Fundamental

#### Como Funciona o Ray-casting?
1. **Para cada coluna de pixels** na tela (ex: 800 colunas)
2. **Calcule o ângulo** do raio correspondente
3. **"Lance" o raio** até encontrar uma parede
4. **Calcule a distância** até a parede
5. **Desenhe uma linha vertical** com altura baseada na distância

#### Algoritmo Básico
```c
void cast_rays(t_game *game) {
    double ray_angle;
    double distance;
    int wall_height;
    
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calcular ângulo do raio atual
        ray_angle = (game->player.angle - game->player.fov/2) + 
                   (x * game->player.fov / SCREEN_WIDTH);
        
        // Lançar raio e calcular distância
        distance = cast_single_ray(game, ray_angle);
        
        // Calcular altura da parede na tela
        wall_height = (int)(SCREEN_HEIGHT / distance);
        
        // Desenhar linha vertical
        draw_vertical_line(game, x, wall_height);
    }
}
```

### 🎯 Implementação do Ray-casting

#### DDA Algorithm (Digital Differential Analyzer)
```c
double cast_single_ray(t_game *game, double angle) {
    double dx = cos(angle);  // Direção X do raio
    double dy = sin(angle);  // Direção Y do raio
    
    double x = game->player.x;
    double y = game->player.y;
    
    // Pequenos incrementos para "caminhar" com o raio
    double step = 0.01;
    
    while (1) {
        x += dx * step;
        y += dy * step;
        
        // Verificar se atingiu uma parede
        if (is_wall(game->map, (int)x, (int)y)) {
            // Retornar distância euclidiana
            return sqrt(pow(x - game->player.x, 2) + 
                       pow(y - game->player.y, 2));
        }
    }
}
```

#### Otimização: Grid Traversal
```c
// Algoritmo mais eficiente - caminha pelos quadrados do grid
typedef struct s_ray {
    double x, y;        // Posição atual
    double dx, dy;      // Direção
    int map_x, map_y;   // Posição no grid do mapa
    double delta_x, delta_y; // Distância até próxima linha do grid
} t_ray;
```

### 🖼️ Texture Mapping

#### Calculando Coordenadas de Textura
```c
void apply_wall_texture(t_game *game, int screen_x, double distance, 
                       double wall_hit_x, double wall_hit_y) {
    // Determinar qual face da parede foi atingida
    int texture_x;
    
    if (hit_vertical_wall) {
        texture_x = (int)(wall_hit_y * TEXTURE_WIDTH) % TEXTURE_WIDTH;
    } else {
        texture_x = (int)(wall_hit_x * TEXTURE_WIDTH) % TEXTURE_WIDTH;
    }
    
    // Desenhar coluna da textura na tela
    draw_textured_column(game, screen_x, texture_x, distance);
}
```

---

## 🖼️ miniLibX - Biblioteca Gráfica

### 🚀 Inicialização e Setup

#### Setup Básico
```c
int init_mlx(t_game *game) {
    game->mlx = mlx_init();
    if (!game->mlx)
        return (handle_error(ERROR_MLX_INIT, "mlx_init"));
    
    game->window = mlx_new_window(game->mlx, SCREEN_WIDTH, 
                                 SCREEN_HEIGHT, "cub3D");
    if (!game->window)
        return (handle_error(ERROR_MLX_INIT, "mlx_new_window"));
    
    // Criar buffer de imagem para melhor performance
    game->image = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->img_data = mlx_get_data_addr(game->image, &game->bits_per_pixel,
                                      &game->line_length, &game->endian);
    
    return (1);
}
```

#### Pixel Manipulation Direta
```c
void put_pixel_to_image(t_game *game, int x, int y, int color) {
    char *dst;
    
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        dst = game->img_data + (y * game->line_length + 
              x * (game->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}
```

### 🎨 Carregamento de Texturas

#### Loading XPM Files
```c
typedef struct s_texture {
    void *img;
    char *data;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_texture;

int load_texture(t_game *game, t_texture *texture, char *path) {
    texture->img = mlx_xpm_file_to_image(game->mlx, path, 
                                        &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    
    texture->data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                     &texture->line_length, &texture->endian);
    return (1);
}
```

#### Texture Sampling
```c
int get_texture_color(t_texture *texture, int x, int y) {
    char *pixel;
    
    if (x >= 0 && x < texture->width && y >= 0 && y < texture->height) {
        pixel = texture->data + (y * texture->line_length + 
                x * (texture->bits_per_pixel / 8));
        return (*(int*)pixel);
    }
    return (0);
}
```

---

## 🗺️ Parsing e Validação de Mapas

### 📄 Estrutura do Arquivo .cub

#### Parser State Machine
```c
typedef enum e_parse_state {
    PARSE_TEXTURES,
    PARSE_COLORS,
    PARSE_MAP,
    PARSE_COMPLETE
} t_parse_state;

typedef struct s_config {
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    t_color floor_color;
    t_color ceiling_color;
    char **map;
    int player_x, player_y;
    char player_direction;
} t_config;
```

#### Parsing Implementation
```c
int parse_cub_file(char *filename, t_config *config) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (handle_error(ERROR_FILE_NOT_FOUND, filename));
    
    char *line;
    t_parse_state state = PARSE_TEXTURES;
    
    while ((line = get_next_line(fd)) != NULL) {
        if (is_empty_line(line)) {
            free(line);
            continue;
        }
        
        switch (state) {
            case PARSE_TEXTURES:
                if (!parse_texture_line(line, config))
                    return (0);
                break;
            case PARSE_COLORS:
                if (!parse_color_line(line, config))
                    return (0);
                break;
            case PARSE_MAP:
                if (!parse_map_line(line, config))
                    return (0);
                break;
        }
        free(line);
    }
    close(fd);
    return (validate_config(config));
}
```

### ✅ Validação de Mapa

#### Map Validation Rules
```c
int validate_map(t_config *config) {
    // 1. Verificar se o mapa está fechado por paredes
    if (!is_map_closed(config->map))
        return (0);
    
    // 2. Verificar se existe exatamente um jogador
    if (!validate_single_player(config))
        return (0);
    
    // 3. Verificar caracteres válidos
    if (!validate_map_characters(config->map))
        return (0);
    
    // 4. Verificar se não há espaços inacessíveis
    if (!validate_reachability(config))
        return (0);
    
    return (1);
}
```

#### Flood Fill Algorithm para Validação
```c
void flood_fill(char **map, int x, int y, char target, char replacement) {
    if (map[y][x] != target)
        return;
    
    map[y][x] = replacement;
    
    // Recursão para 4 direções
    flood_fill(map, x+1, y, target, replacement);
    flood_fill(map, x-1, y, target, replacement);
    flood_fill(map, x, y+1, target, replacement);
    flood_fill(map, x, y-1, target, replacement);
}
```

---

## 🎮 Controles e Eventos

### ⌨️ Sistema de Input

#### Event Handling Setup
```c
int setup_events(t_game *game) {
    // Key press events
    mlx_hook(game->window, 2, 1L<<0, key_press, game);
    mlx_hook(game->window, 3, 1L<<1, key_release, game);
    
    // Mouse events (bonus)
    mlx_hook(game->window, 4, 1L<<2, mouse_press, game);
    mlx_hook(game->window, 6, 1L<<6, mouse_move, game);
    
    // Window events
    mlx_hook(game->window, 17, 1L<<17, close_window, game);
    
    // Game loop
    mlx_loop_hook(game->mlx, game_loop, game);
    
    return (1);
}
```

#### Movement System
```c
typedef struct s_input {
    int w, a, s, d;        // Movement keys
    int left, right;       // Rotation keys
    int mouse_x, mouse_y;  // Mouse position
} t_input;

void update_player_movement(t_game *game, double delta_time) {
    double move_speed = 5.0 * delta_time;
    double rot_speed = 3.0 * delta_time;
    
    // Forward/Backward movement
    if (game->input.w) {
        double new_x = game->player.x + cos(game->player.angle) * move_speed;
        double new_y = game->player.y + sin(game->player.angle) * move_speed;
        
        if (!is_wall(game->map, (int)new_x, (int)new_y)) {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
    // Rotation
    if (game->input.left)
        game->player.angle -= rot_speed;
    if (game->input.right)
        game->player.angle += rot_speed;
    
    // Normalize angle
    while (game->player.angle < 0) game->player.angle += 2 * M_PI;
    while (game->player.angle >= 2 * M_PI) game->player.angle -= 2 * M_PI;
}
```

#### Collision Detection
```c
int check_collision(t_game *game, double new_x, double new_y) {
    // Check corners of player bounding box
    double radius = 0.2;  // Player radius
    
    if (is_wall(game->map, (int)(new_x + radius), (int)(new_y + radius)) ||
        is_wall(game->map, (int)(new_x - radius), (int)(new_y + radius)) ||
        is_wall(game->map, (int)(new_x + radius), (int)(new_y - radius)) ||
        is_wall(game->map, (int)(new_x - radius), (int)(new_y - radius))) {
        return (1);  // Collision detected
    }
    return (0);  // No collision
}
```

---

## 🔧 Otimização e Performance

### ⚡ Performance Tips

#### Frame Rate Control
```c
int game_loop(t_game *game) {
    static long last_time = 0;
    long current_time = get_time_ms();
    double delta_time = (current_time - last_time) / 1000.0;
    
    if (delta_time < 1.0/60.0)  // Limit to 60 FPS
        return (0);
    
    update_game(game, delta_time);
    render_frame(game);
    
    last_time = current_time;
    return (0);
}
```

#### Memory Optimization
```c
// Pre-calculate trigonometric values
typedef struct s_trig_table {
    double sin_table[360];
    double cos_table[360];
} t_trig_table;

void init_trig_table(t_trig_table *table) {
    for (int i = 0; i < 360; i++) {
        double angle = i * M_PI / 180.0;
        table->sin_table[i] = sin(angle);
        table->cos_table[i] = cos(angle);
    }
}
```

#### Ray-casting Optimization
```c
// Use integer DDA for faster ray traversal
typedef struct s_dda {
    int map_x, map_y;
    double delta_dist_x, delta_dist_y;
    double side_dist_x, side_dist_y;
    int step_x, step_y;
    int hit;
    int side;
} t_dda;
```

---

## 🎁 Features Bonus

### 🗺️ Minimap Implementation

#### Minimap Rendering
```c
void render_minimap(t_game *game) {
    int map_scale = 10;  // Pixels per map unit
    int minimap_x = 10;  // Top-left corner
    int minimap_y = 10;
    
    // Draw map grid
    for (int y = 0; y < game->map_height; y++) {
        for (int x = 0; x < game->map_width; x++) {
            int color = (game->map[y][x] == '1') ? 0xFFFFFF : 0x000000;
            
            draw_square(game, minimap_x + x * map_scale,
                       minimap_y + y * map_scale, map_scale, color);
        }
    }
    
    // Draw player position
    int player_screen_x = minimap_x + (int)(game->player.x * map_scale);
    int player_screen_y = minimap_y + (int)(game->player.y * map_scale);
    draw_circle(game, player_screen_x, player_screen_y, 3, 0xFF0000);
    
    // Draw player direction
    int dir_x = player_screen_x + (int)(cos(game->player.angle) * 15);
    int dir_y = player_screen_y + (int)(sin(game->player.angle) * 15);
    draw_line(game, player_screen_x, player_screen_y, dir_x, dir_y, 0xFF0000);
}
```

### 🚪 Door System

#### Door Structure
```c
typedef struct s_door {
    int x, y;              // Position in map
    double open_amount;    // 0.0 = closed, 1.0 = open
    int is_opening;        // Animation state
    double open_speed;     // Animation speed
} t_door;

typedef struct s_doors {
    t_door *doors;
    int count;
} t_doors;
```

#### Door Interaction
```c
void interact_with_door(t_game *game) {
    // Calculate position in front of player
    double interact_x = game->player.x + cos(game->player.angle) * 1.5;
    double interact_y = game->player.y + sin(game->player.angle) * 1.5;
    
    // Check if there's a door at this position
    t_door *door = find_door(game->doors, (int)interact_x, (int)interact_y);
    if (door) {
        door->is_opening = !door->is_opening;
    }
}
```

### 🎭 Animated Sprites

#### Sprite System
```c
typedef struct s_sprite {
    double x, y;           // World position
    t_texture *textures;   // Animation frames
    int frame_count;
    int current_frame;
    double animation_speed;
    double last_frame_time;
} t_sprite;

void update_sprite_animation(t_sprite *sprite, double current_time) {
    if (current_time - sprite->last_frame_time > sprite->animation_speed) {
        sprite->current_frame = (sprite->current_frame + 1) % sprite->frame_count;
        sprite->last_frame_time = current_time;
    }
}
```

---

## 🐛 Debug e Testes

### 🔍 Debugging Tools

#### Debug Visualization
```c
void debug_render_rays(t_game *game) {
    if (!game->debug_mode) return;
    
    // Draw all rays in minimap
    for (int i = 0; i < SCREEN_WIDTH; i += 10) {  // Every 10th ray
        double angle = (game->player.angle - game->player.fov/2) + 
                      (i * game->player.fov / SCREEN_WIDTH);
        
        double end_x = game->player.x + cos(angle) * 20;
        double end_y = game->player.y + sin(angle) * 20;
        
        draw_debug_line(game, game->player.x, game->player.y, 
                       end_x, end_y, 0x00FF00);
    }
}
```

#### Memory Leak Detection
```c
#ifdef DEBUG
    #define MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
    #define FREE(ptr) debug_free(ptr, __FILE__, __LINE__)
    
    void *debug_malloc(size_t size, char *file, int line) {
        void *ptr = malloc(size);
        printf("MALLOC: %p (%zu bytes) at %s:%d\n", ptr, size, file, line);
        return ptr;
    }
#else
    #define MALLOC(size) malloc(size)
    #define FREE(ptr) free(ptr)
#endif
```

### 🧪 Test Cases

#### Unit Tests Structure
```c
typedef struct s_test {
    char *name;
    int (*test_function)(void);
} t_test;

int run_tests(t_test *tests, int count) {
    int passed = 0;
    
    for (int i = 0; i < count; i++) {
        printf("Running test: %s... ", tests[i].name);
        if (tests[i].test_function()) {
            printf("PASS\n");
            passed++;
        } else {
            printf("FAIL\n");
        }
    }
    
    printf("Tests passed: %d/%d\n", passed, count);
    return (passed == count);
}
```

#### Map Validation Tests
```c
int test_valid_map(void) {
    char *test_map[] = {
        "111111",
        "100001",
        "100N01",
        "100001",
        "111111",
        NULL
    };
    
    t_config config = {0};
    config.map = test_map;
    
    return validate_map(&config);
}

int test_invalid_map_no_walls(void) {
    char *test_map[] = {
        "000000",
        "000000",
        "00N000",
        "000000",
        "000000",
        NULL
    };
    
    t_config config = {0};
    config.map = test_map;
    
    return !validate_map(&config);  // Should return false
}
```

---

## 🎓 Cronograma de Estudos Sugerido

### 📅 Semana 1: Fundamentos
- **Dias 1-2**: Matemática (trigonometria, vetores)
- **Dias 3-4**: Conceitos de computação gráfica
- **Dias 5-7**: Review de programação C avançada

### 📅 Semana 2: Ray-casting Core
- **Dias 1-3**: Teoria e algoritmo básico de ray-casting
- **Dias 4-5**: Implementação do DDA
- **Dias 6-7**: Testes e debugging

### 📅 Semana 3: Interface e Controles
- **Dias 1-3**: miniLibX e manipulação de pixels
- **Dias 4-5**: Sistema de eventos e controles
- **Dias 6-7**: Parsing de arquivos .cub

### 📅 Semana 4: Finalização e Bonus
- **Dias 1-2**: Textures e otimização
- **Dias 3-5**: Features bonus (minimap, doors, sprites)
- **Dias 6-7**: Testes finais e polish

---

## 🎯 Exercícios Práticos Recomendados

### 🔢 Matemática
1. **Implementar rotação de vetores** sem usar bibliotecas
2. **Calcular intersecção** linha-retângulo
3. **Criar função de interpolação** para movimentos suaves

### 🖥️ Programação
1. **Parser simples** para arquivos de configuração
2. **Sistema de gerenciamento** de memória com leak detection
3. **Máquina de estados** para diferentes modos do jogo

### 🎮 Ray-casting
1. **Implementar ray-casting 2D** que desenha no terminal
2. **Versão simplificada** com ASCII art
3. **Benchmark diferentes** algoritmos de ray-casting

---

## 📚 Recursos Adicionais

### 📖 Bibliografia Essencial
- **"Computer Graphics: Principles and Practice"** - Hughes, van Dam
- **"Real-Time Rendering"** - Akenine-Möller, Haines
- **Tutoriais online**: Lode's Computer Graphics Tutorial

### 🔗 Links Úteis
- [Ray-casting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)

### 🛠️ Ferramentas de Desenvolvimento
- **Valgrind**: Para detecção de memory leaks
- **GDB**: Para debugging passo-a-passo
- **Norminette**: Para verificar normas da 42
