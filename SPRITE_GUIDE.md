# 🎨 Guia de Sprites - Cub3D

## 📋 Formato da Imagem PNG

### Requisitos Obrigatórios:
- **Formato**: PNG com canal alpha (RGBA)
- **Fundo**: Transparente (alpha = 0)
- **Tamanho recomendado**: 64x64, 128x128 ou 256x256 pixels
- **Orientação**: Sprite de frente (visível de todos os ângulos)

### Como funciona:
O código verifica a transparência de cada pixel:
```c
if ((color & 0xFF) > 0)  // Se alpha > 0, renderiza o pixel
    mlx_put_pixel(eng->frame, x, y, color);
```

## 🖼️ Exemplos de Sprites

### ✅ Bom (com transparência):
```
Coluna/Pilar:
┌─────────┐
│    █    │  ← Pixels opacos (visíveis)
│   ███   │
│  █████  │
│   ███   │
│    █    │
└─────────┘
   ↑ Fundo transparente (invisível)
```

### ❌ Ruim (sem transparência):
```
┌─────────┐
│░░░░█░░░░│  ← Fundo branco/colorido
│░░░███░░░│     (renderiza quadrado feio)
│░░█████░░│
│░░░███░░░│
│░░░░█░░░░│
└─────────┘
```

## 📝 Como configurar no arquivo .cub

### Sintaxe:
```
SP <caminho_para_sprite.png>
```

### Exemplo completo:
```bash
NO ./maps/textures/north.png
SO ./maps/textures/south.png
WE ./maps/textures/west.png
EA ./maps/textures/east.png
SP ./maps/textures/my_sprite.png    # ← Nova linha para sprite

F 50,50,50
C 135,206,235

111111
100001
10P001   # P = posição do sprite no mapa
100001
111111
```

## 🎯 Posicionamento no Mapa

Use o caractere `P` no mapa para indicar onde os sprites aparecem:

```
1111111111
1000P00001   ← Sprite na posição (4, 1)
1000000001
1000P00001   ← Outro sprite na posição (4, 3)
1111111111
```

## 🔧 Ferramentas Recomendadas

### Para criar sprites:
- **GIMP** (grátis): https://www.gimp.org/
- **Krita** (grátis): https://krita.org/
- **Photoshop** (pago)
- **Aseprite** (pixel art): https://www.aseprite.org/

### Como criar no GIMP:
1. Novo arquivo → 128x128 pixels
2. Camada → Transparência → Adicionar Canal Alpha
3. Desenhar o sprite
4. Exportar como PNG
5. ✅ Manter configuração "Salvar informação de cor de fundo" **desmarcada**

## 🎨 Ideias de Sprites

- 🕯️ Velas
- 🌳 Árvores
- 🗿 Estátuas
- 💎 Cristais
- 🏺 Vasos
- ⚔️ Armas
- 🛡️ Escudos
- 👻 Inimigos
- 💰 Tesouros
- 🔥 Fogo

## ⚠️ Notas Importantes

1. **Performance**: Sprites com muito detalhe (>256x256) podem ser lentos
2. **Oclusão**: Sprites são renderizados DEPOIS das paredes (z-buffer)
3. **Visibilidade**: Sprites são visíveis de 360° (sempre de frente)
4. **Múltiplos sprites**: Use o mesmo PNG para todos (por enquanto)
5. **Animação**: Sistema suporta múltiplos frames (futuro)

## 🐛 Troubleshooting

### Sprite não aparece:
- ✅ Verifique se o path está correto no .cub
- ✅ Confirme que há caracteres 'P' no mapa
- ✅ Verifique se a imagem tem canal alpha
- ✅ Teste com uma imagem menor primeiro

### Sprite aparece como quadrado:
- ❌ Imagem não tem fundo transparente
- ✅ Reexporte com canal alpha habilitado

### Sprite aparece através de paredes:
- 🔧 Bug no z-buffer (reportar)

---

**Exemplo pronto**: `maps/test_sprites.cub`
**Textura de exemplo**: `maps/textures/north.png` (temporário)
