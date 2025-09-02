import pygame 

pygame.init()

#colores
BLACK = (0,0,0)
WHITE = (255,255,255)
GREEN = (0,255,0)
RED = (255,0,0)
BLUE = (0,0,255)
DARK_GRAY = (30,30,30)

#crear ventana
size = (1350,700)
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()
done = False
#img_ventanila = pygame.image.load("").convert()
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: done = True
        if event.type == pygame.MOUSEBUTTONDOWN:
            x, y = event.pos
            print(f"Click en: ({x}, {y})")

    screen.fill(DARK_GRAY)
    #screen.blit(img_ventanilla, [160,100])
    pygame.draw.line(screen, BLACK, [20,100], [100,100], 4)
    pygame.display.flip() #actualizar pantalla
    clock.tick(60)