# 📋 Backlog de Desenvolvimento - cub3D Project

---

## 🎯 Metodologia de Trabalho

### 🤝 Divisão de Responsabilidades
- **Dev A**: Foco em **Parsing & Validation** + **Math & Utils**
- **Dev B**: Foco em **Ray-casting & Graphics** + **Input & Events**
- **Ambos**: **Integration** + **Testing** + **Bonus Features**

### 🔄 Workflow Git
1. **Feature Branches**: `feature/module-name`
2. **Pull Requests**: Code review obrigatório
3. **Integration Branch**: `develop` para integração
4. **Main Branch**: `main` para versões estáveis

---

## 📊 Status Tracking

### 🏷️ Labels de Status
- 🔴 **TODO**: Não iniciado
- 🟡 **IN PROGRESS**: Em desenvolvimento
- 🟢 **DONE**: Concluído
- 🔵 **REVIEW**: Aguardando code review
- 🟣 **BLOCKED**: Bloqueado (dependência)

---

## 🏗️ FASE 1: Fundações e Estrutura Base

### 📚 1.1 Setup Inicial e Estrutura do Projeto
**Responsável**: Dev A + Dev B (Pair Programming)  
**Branch**: `feature/project-setup`  
**Estimativa**: 2 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Criar estrutura de diretórios padrão
  ```
  ├── src/
  ├── include/
  ├── lib/libft/
  ├── lib/minilibx/
  ├── maps/
  ├── textures/
  ├── tests/
  └── Makefile
  ```
- [ ] Configurar Makefile com regras básicas
- [ ] Definir headers principais (`cub3d.h`, `structs.h`, `constants.h`)
- [ ] Setup de norminette e ferramentas de desenvolvimento
- [ ] Criar .gitignore apropriado
- [ ] Documentar convenções de código no README

#### Critérios de Aceitação:
- Projeto compila sem erros
- Norminette passa em todos os arquivos
- Estrutura de diretórios seguindo padrões da 42

---

### 🧮 1.2 Estruturas de Dados Core
**Responsável**: Dev A  
**Branch**: `feature/core-structures`  
**Dependências**: 1.1  
**Estimativa**: 3 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Definir `t_player` (posição, ângulo, FOV)
- [ ] Definir `t_map` (grid, dimensões, texturas)
- [ ] Definir `t_game` (state principal do jogo)
- [ ] Definir `t_ray` (para ray-casting)
- [ ] Definir `t_image` (buffer de imagem)
- [ ] Criar funções de inicialização para cada struct
- [ ] Implementar funções de limpeza de memória
- [ ] Documentar todas as estruturas com comentários

#### Critérios de Aceitação:
- Todas as structs definidas e documentadas
- Funções de init/free implementadas
- Sem memory leaks (testado com valgrind)
- Code review aprovado

---

### 🔧 1.3 Utilitários Matemáticos
**Responsável**: Dev A  
**Branch**: `feature/math-utils`  
**Dependências**: 1.2  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar funções trigonométricas básicas
  - [ ] `deg_to_rad()` e `rad_to_deg()`
  - [ ] `normalize_angle()` (manter entre 0 e 2π)
- [ ] Implementar operações com vetores 2D
  - [ ] `vector_add()`, `vector_subtract()`
  - [ ] `vector_multiply()`, `vector_magnitude()`
  - [ ] `vector_distance()`
- [ ] Implementar funções de interpolação
  - [ ] `lerp()` (linear interpolation)
  - [ ] `smooth_step()` para animações
- [ ] Criar lookup tables para sin/cos (otimização)
- [ ] Implementar testes unitários para funções matemáticas

#### Critérios de Aceitação:
- Todas as funções matemáticas testadas
- Lookup tables funcionando corretamente
- Performance adequada (benchmarks)
- Documentação completa com exemplos

---

## 🗺️ FASE 2: Parsing e Validação de Mapas

### 📄 2.1 Parser Base para Arquivos .cub
**Responsável**: Dev A  
**Branch**: `feature/cub-parser`  
**Dependências**: 1.2, 1.3  
**Estimativa**: 6 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar leitura de arquivo linha por linha
- [ ] Criar state machine para parsing
  - [ ] Estado: TEXTURES
  - [ ] Estado: COLORS  
  - [ ] Estado: MAP
- [ ] Parser para texturas (NO, SO, WE, EA)
- [ ] Parser para cores (F, C) com validação RGB
- [ ] Tratamento de linhas vazias e comentários
- [ ] Sistema robusto de error handling
- [ ] Testes com arquivos válidos e inválidos

#### Critérios de Aceitação:
- Parse correto de todos os elementos do .cub
- Error handling robusto com mensagens claras
- Memória liberada corretamente em caso de erro
- Testes passando para casos válidos e inválidos

---

### 🗺️ 2.2 Parser e Validação de Mapas
**Responsável**: Dev A  
**Branch**: `feature/map-validation`  
**Dependências**: 2.1  
**Estimativa**: 8 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Parser para grid do mapa
  - [ ] Suporte a espaços e caracteres válidos
  - [ ] Detecção automática de dimensões
- [ ] Validação de caracteres permitidos (0, 1, N, S, E, W)
- [ ] Validação de jogador único
- [ ] Implementar flood fill para verificar se mapa está fechado
- [ ] Validação de acessibilidade (todos os espaços alcançáveis)
- [ ] Conversão de caracteres de direção para ângulos
- [ ] Sistema de debugging para visualizar validação
- [ ] Testes extensivos com mapas edge-case

#### Critérios de Aceitação:
- Validação robusta de todos os requisitos de mapa
- Flood fill funcionando corretamente
- Detecção precisa de mapas inválidos
- Performance adequada para mapas grandes
- Suite de testes abrangente

---

## 🎨 FASE 3: Sistema Gráfico Base

### 🖼️ 3.1 Inicialização e Setup do miniLibX
**Responsável**: Dev B  
**Branch**: `feature/mlx-setup`  
**Dependências**: 1.2  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Inicialização do mlx
- [ ] Criação de janela com dimensões configuráveis
- [ ] Setup de image buffer para double buffering
- [ ] Funções básicas de pixel manipulation
- [ ] Sistema de limpeza e encerramento limpo
- [ ] Tratamento de eventos básicos (fechar janela)
- [ ] Testes de inicialização em diferentes ambientes

#### Critérios de Aceitação:
- mlx inicializa corretamente
- Janela abre e fecha sem erros
- Image buffer funciona corretamente
- Pixel manipulation otimizada
- Cleanup completo de recursos

---

### 🎨 3.2 Sistema de Cores e Pixel Manipulation
**Responsável**: Dev B  
**Branch**: `feature/color-system`  
**Dependências**: 3.1  
**Estimativa**: 3 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar estrutura `t_color` (RGB + Alpha)
- [ ] Funções de conversão (RGB ↔ Hex ↔ Int)
- [ ] Sistema de shading baseado em distância
- [ ] Interpolação de cores para gradientes
- [ ] Funções de drawing primitivas
  - [ ] `draw_pixel()`, `draw_line()`
  - [ ] `draw_rectangle()`, `draw_circle()`
- [ ] Testes visuais para todas as funções de cor

#### Critérios de Aceitação:
- Conversões de cor funcionando perfeitamente
- Shading gradual implementado
- Primitivas de drawing funcionais
- Performance otimizada para manipulação de pixels

---

### 🖼️ 3.3 Sistema de Carregamento de Texturas
**Responsável**: Dev B  
**Branch**: `feature/texture-system`  
**Dependências**: 3.2  
**Estimativa**: 5 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Estrutura `t_texture` para gerenciar texturas
- [ ] Carregamento de arquivos XPM
- [ ] Sistema de cache de texturas
- [ ] Funções de sampling de texturas
- [ ] Validation de arquivos de textura
- [ ] Sistema de fallback para texturas missing
- [ ] Memory management para texturas
- [ ] Testes com diferentes formatos e tamanhos

#### Critérios de Aceitação:
- Carregamento robusto de texturas XPM
- Sistema de cache eficiente
- Sampling preciso de pixels
- Error handling para arquivos inválidos
- Sem memory leaks

---

## 🔦 FASE 4: Ray-casting Core

### 📐 4.1 Algoritmo Básico de Ray-casting
**Responsável**: Dev B  
**Branch**: `feature/basic-raycasting`  
**Dependências**: 3.1, 3.2, 1.3  
**Estimativa**: 10 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar algoritmo básico de ray-casting
  - [ ] Cálculo de ângulos para cada coluna da tela
  - [ ] Lançamento de raios com step pequeno
  - [ ] Detecção de colisão com paredes
- [ ] Cálculo de distâncias euclidianas
- [ ] Correção de fish-eye effect
- [ ] Projeção de altura de paredes na tela
- [ ] Renderização de colunas verticais básicas
- [ ] Sistema de debug visual (mostrar raios)
- [ ] Testes de performance e precisão

#### Critérios de Aceitação:
- Ray-casting básico funcionando
- Projeção correta de paredes
- Fish-eye effect corrigido
- Performance aceitável (>30 FPS)
- Debug visual implementado

---

### ⚡ 4.2 Otimização com DDA Algorithm
**Responsável**: Dev B  
**Branch**: `feature/dda-optimization`  
**Dependências**: 4.1  
**Estimativa**: 8 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar DDA (Digital Differential Analyzer)
- [ ] Grid traversal otimizado
- [ ] Detecção de hit em faces verticais vs horizontais
- [ ] Cálculo preciso de coordenadas de hit
- [ ] Comparação de performance (basic vs DDA)
- [ ] Refatoração para usar DDA como padrão
- [ ] Testes de precisão em casos edge
- [ ] Documentação detalhada do algoritmo

#### Critérios de Aceitação:
- DDA implementado corretamente
- Performance significativamente melhor
- Precisão mantida ou melhorada
- Detecção correta de faces de parede
- Benchmarks documentados

---

### 🎨 4.3 Texture Mapping em Paredes
**Responsável**: Dev B  
**Branch**: `feature/wall-textures`  
**Dependências**: 4.2, 3.3, 2.2  
**Estimativa**: 6 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Calcular coordenadas de textura para cada hit
- [ ] Mapear faces de parede para texturas corretas (N, S, E, W)
- [ ] Implementar texture sampling vertical
- [ ] Sistema de scaling de texturas
- [ ] Otimização de acesso à textura
- [ ] Correção de distorções de textura
- [ ] Testes com diferentes tamanhos de textura
- [ ] Debug visual para coordenadas de textura

#### Critérios de Aceitação:
- Texturas aplicadas corretamente em todas as faces
- Mapping preciso de coordenadas
- Performance mantida com texturas
- Sem distorções visuais
- Suporte a texturas de diferentes tamanhos

---

## 🎮 FASE 5: Sistema de Input e Controles

### ⌨️ 5.1 Sistema de Eventos Base
**Responsável**: Dev B  
**Branch**: `feature/input-system`  
**Dependências**: 3.1  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Setup de hooks para eventos de teclado
- [ ] Sistema de estado para teclas (pressed/released)
- [ ] Event handlers para teclas específicas
- [ ] Hook para fechamento de janela (ESC, X)
- [ ] Sistema de input buffering
- [ ] Prevenção de input spam
- [ ] Testes de responsividade

#### Critérios de Aceitação:
- Detecção precisa de key press/release
- Sistema de estado funcionando
- Responsividade adequada
- Cleanup limpo de eventos
- ESC e X fecham o programa corretamente

---

### 🚶 5.2 Sistema de Movimento do Jogador
**Responsável**: Dev B  
**Branch**: `feature/player-movement`  
**Dependências**: 5.1, 4.1, 1.3  
**Estimativa**: 6 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar movimento WASD
  - [ ] W/S: movimento frente/trás
  - [ ] A/D: movimento lateral (strafe)
- [ ] Implementar rotação com setas
- [ ] Sistema de velocidade configurável
- [ ] Delta time para movimento frame-independent
- [ ] Normalização de movimento diagonal
- [ ] Smooth movement interpolation
- [ ] Testes de movimento em diferentes FPS

#### Critérios de Aceitação:
- Movimento suave em todas as direções
- Rotação precisa e responsiva
- Velocidade consistente independente do FPS
- Movimento diagonal normalizado
- Controles intuitivos e naturais

---

### 🚧 5.3 Sistema de Detecção de Colisão
**Responsável**: Dev B  
**Branch**: `feature/collision-system`  
**Dependências**: 5.2, 2.2  
**Estimativa**: 5 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar bounding box para jogador
- [ ] Detecção de colisão com paredes
- [ ] Sistema de sliding collision
- [ ] Prevenção de clipping através de paredes
- [ ] Collision detection otimizada
- [ ] Debug visual para collision boxes
- [ ] Testes edge-case (cantos, espaços pequenos)

#### Critérios de Aceitação:
- Jogador não atravessa paredes
- Sliding collision funcionando suavemente
- Performance otimizada
- Comportamento natural em cantos
- Debug visual útil para desenvolvimento

---

## 🔄 FASE 6: Integração e Renderização Completa

### 🎨 6.1 Sistema de Renderização de Chão e Teto
**Responsável**: Dev A  
**Branch**: `feature/floor-ceiling`  
**Dependências**: 4.3, 2.1  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Renderização de chão com cor sólida
- [ ] Renderização de teto com cor sólida
- [ ] Sistema de gradiente para profundidade
- [ ] Otimização de fill de áreas grandes
- [ ] Configuração via arquivo .cub
- [ ] Testes de performance

#### Critérios de Aceitação:
- Chão e teto renderizados corretamente
- Cores configuráveis via .cub
- Performance otimizada
- Transições suaves com paredes

---

### 🔄 6.2 Game Loop Principal
**Responsável**: Dev A + Dev B (Pair Programming)  
**Branch**: `feature/main-game-loop`  
**Dependências**: 4.3, 5.3, 6.1  
**Estimativa**: 3 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Implementar loop principal do jogo
- [ ] Controle de frame rate (target 60 FPS)
- [ ] Sequência de update/render
- [ ] Performance monitoring
- [ ] System para pausar/resume
- [ ] Cleanup no encerramento

#### Critérios de Aceitação:
- Loop estável rodando a 60 FPS
- Sequência correta de operações
- Performance consistente
- Encerramento limpo

---

### 🔗 6.3 Integração Final dos Módulos
**Responsável**: Dev A + Dev B (Pair Programming)  
**Branch**: `feature/final-integration`  
**Dependências**: Todos os anteriores  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Integração completa de todos os módulos
- [ ] Resolução de conflitos de dependências
- [ ] Testes de integração abrangentes
- [ ] Otimização de performance geral
- [ ] Ajustes finais de balanceamento
- [ ] Validação com diferentes mapas

#### Critérios de Aceitação:
- Todos os módulos funcionando juntos
- Performance target atingida
- Sem memory leaks
- Comportamento consistente
- Ready para avaliação

---

## 🎁 FASE 7: Features Bonus (Opcional)

### 🗺️ 7.1 Sistema de Minimap
**Responsável**: Dev A  
**Branch**: `feature/minimap`  
**Dependências**: 6.3  
**Estimativa**: 6 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Renderização do mapa em escala reduzida
- [ ] Indicador de posição do jogador
- [ ] Indicador de direção do olhar
- [ ] Sistema de zoom configurável
- [ ] Posicionamento configurável na tela
- [ ] Toggle on/off do minimap

#### Critérios de Aceitação:
- Minimap preciso e atualizado em tempo real
- Indicadores visuais claros
- Performance impact mínimo
- Interface intuitiva

---

### 🚪 7.2 Sistema de Portas Interativas
**Responsável**: Dev B  
**Branch**: `feature/doors`  
**Dependências**: 6.3  
**Estimativa**: 8 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Adicionar caractere 'D' para portas no mapa
- [ ] Sistema de estados para portas (fechada/abrindo/aberta/fechando)
- [ ] Animação suave de abertura/fechamento
- [ ] Detecção de interação (tecla E próximo à porta)
- [ ] Atualização dinâmica do sistema de colisão
- [ ] Som de porta (se aplicável)

#### Critérios de Aceitação:
- Portas funcionando com interação natural
- Animações suaves e realistas
- Integração perfeita com ray-casting
- Sem glitches visuais

---

### 🎭 7.3 Sistema de Sprites Animados
**Responsável**: Dev A  
**Branch**: `feature/animated-sprites`  
**Dependências**: 7.2  
**Estimativa**: 10 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Sistema de sprites billboard
- [ ] Carregamento de múltiplos frames
- [ ] Sistema de animação temporal
- [ ] Z-buffering para ordem de renderização
- [ ] Scaling baseado em distância
- [ ] Diferentes tipos de sprites (estático/animado)

#### Critérios de Aceitação:
- Sprites renderizados corretamente no mundo 3D
- Animações fluidas
- Z-buffering funcional
- Performance adequada com múltiplos sprites

---

### 🖱️ 7.4 Controle por Mouse
**Responsável**: Dev B  
**Branch**: `feature/mouse-control`  
**Dependências**: 7.1  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Captura de movimento do mouse
- [ ] Conversão de movimento para rotação
- [ ] Sistema de sensibilidade configurável
- [ ] Mouse capture/release
- [ ] Suavização de movimento
- [ ] Toggle mouse/keyboard

#### Critérios de Aceitação:
- Controle natural e responsivo
- Sensibilidade ajustável
- Suavização adequada
- Possibilidade de alternar entre mouse e teclado

---

## 🧪 FASE 8: Testes e Qualidade

### 🔍 8.1 Suite de Testes Unitários
**Responsável**: Dev A  
**Branch**: `feature/unit-tests`  
**Dependências**: Paralelo ao desenvolvimento  
**Estimativa**: 8 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Testes para funções matemáticas
- [ ] Testes para parsing de .cub
- [ ] Testes para validação de mapas
- [ ] Testes para ray-casting básico
- [ ] Framework de testing simples
- [ ] Coverage report básico

#### Critérios de Aceitação:
- Cobertura mínima de 70% das funções críticas
- Todos os testes passando
- Framework de teste funcionando
- Fácil adição de novos testes

---

### 🐛 8.2 Debugging e Ferramentas de Desenvolvimento
**Responsável**: Dev B  
**Branch**: `feature/debug-tools`  
**Dependências**: Paralelo ao desenvolvimento  
**Estimativa**: 4 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Sistema de debug visual para raios
- [ ] FPS counter na tela
- [ ] Memory usage monitor
- [ ] Debug console com comandos
- [ ] Sistema de logging configurável
- [ ] Profiling de performance

#### Critérios de Aceitação:
- Ferramentas de debug úteis e funcionais
- Performance monitoring preciso
- Debug visual claro e informativo
- Sistema de logging configurável

---

### ✅ 8.3 Testes de Integração e Validação Final
**Responsável**: Dev A + Dev B  
**Branch**: `feature/integration-tests`  
**Dependências**: 6.3  
**Estimativa**: 6 horas  
**Status**: 🔴 TODO

#### Tarefas:
- [ ] Testes com diferentes mapas complexos
- [ ] Testes de stress (mapas grandes)
- [ ] Validação de memory leaks com valgrind
- [ ] Testes de performance em diferentes ambientes
- [ ] Verificação final da norminette
- [ ] Testes de edge cases

#### Critérios de Aceitação:
- Todos os testes passando
- Sem memory leaks detectados
- Performance adequada em todos os cenários
- Código conforme normas da 42
- Ready para avaliação final

---

## 📊 Métricas de Qualidade

### 🎯 Targets de Performance
- **FPS Target**: Mínimo 30 FPS, ideal 60 FPS
- **Memory Usage**: Máximo 50MB em runtime
- **Startup Time**: Máximo 2 segundos para carregar
- **Map Loading**: Máximo 1 segundo para mapas grandes

### 🔍 Critérios de Code Quality
- **Norminette**: 100% compliance
- **Memory Leaks**: Zero leaks detectados
- **Test Coverage**: Mínimo 70% das funções críticas
- **Documentation**: Todas as funções públicas documentadas

---

## 🗓️ Timeline Sugerido

### **Sprint 1** (Semana 1): Fundações
- FASE 1: Fundações e Estrutura Base
- FASE 2: Parsing e Validação de Mapas

### **Sprint 2** (Semana 2): Gráficos Core
- FASE 3: Sistema Gráfico Base
- FASE 4: Ray-casting Core

### **Sprint 3** (Semana 3): Interação
- FASE 5: Sistema de Input e Controles
- FASE 6: Integração e Renderização Completa

### **Sprint 4** (Semana 4): Finalização
- FASE 7: Features Bonus (opcional)
- FASE 8: Testes e Qualidade

---

## 🚨 Pontos de Atenção e Riscos

### ⚠️ Riscos Técnicos
- **Complexidade do DDA**: Algoritmo pode ser difícil de implementar
- **Performance**: Ray-casting pode ser lento se mal otimizado
- **Memory Management**: Muitas estruturas dinâmicas
- **Integration**: Módulos podem ter conflitos

### 🔧 Mitigações
- **Pair Programming**: Para partes críticas
- **Code Review**: Obrigatório para todos os PRs
- **Testing Contínuo**: Testes unitários desde o início
- **Prototyping**: Validar conceitos antes da implementação

---

## 📝 Convenções de Desenvolvimento

### 🏷️ Naming Conventions
- **Variáveis**: `snake_case`
- **Funções**: `snake_case`
- **Structs**: `t_struct_name`
- **Constants**: `UPPER_CASE`
- **Files**: `snake_case.c/h`

### 📂 Code Organization
- **1 conceito por arquivo**: Evitar arquivos muito grandes
- **Headers claros**: Documentar interfaces públicas
- **Error handling**: Consistente em todo o projeto
- **Memory management**: Always free what you malloc

### 📋 PR Template
```
## Descrição
Breve descrição das mudanças

## Checklist
- [ ] Código segue norminette
- [ ] Testes unitários passando
- [ ] Sem memory leaks
- [ ] Documentação atualizada
- [ ] Performance testada

## Testing
Como testar essas mudanças
```
