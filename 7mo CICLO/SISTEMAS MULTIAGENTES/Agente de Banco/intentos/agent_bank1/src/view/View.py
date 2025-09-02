import pygame 
from model.constantes import DARK_GRAY,BLACK,BLUE,GRAY,GREEN,RED,WHITE

class View:
    def __init__(self, ancho, largo):
        self.pantalla = pygame.display.set_mode((ancho, largo))
        self.pantalla.fill(DARK_GRAY)
        self.init_view()
        pygame.display.set_caption("Simulación de Agente Bancario")

    def dibujar(self, elementos):
        # Limpiar pantalla
        self.pantalla.fill((255, 255, 255))  # Fondo blanco o imagen
        self.pantalla.fill(DARK_GRAY)
        self.dibujarFila()
        self.dibujarHuella()
        pygame.draw.line(self.pantalla, (0, 0, 0), (657, 0), (657, 40), 5)
        self.dibujarCuadroTexto("ENTRADA", (0, 255, 0), 910, 650, 100, 40, 3)
        self.dibujarCuadroTexto("SALIDA", (255, 0, 0), 240, 650, 100, 40, 3)
        self.dibujarCuadroTexto("SALIDA", (255, 0, 0), 1110, 650, 100, 40, 3)
        self.dibujarCuadroTexto("", (0, 0, 0), 550, 40, 220, 130, 7)
        self.dibujarCuadroTexto("1", (0, 0, 255), 150, 65, 30, 30, 2)
        self.dibujarCuadroTexto("2", (0, 0, 255), 440, 65, 30, 30, 2)
        self.dibujarCuadroTexto("3", (0, 0, 255), 850, 65, 30, 30, 2)
        self.dibujarCuadroTexto("4", (0, 0, 255), 1140, 65, 30, 30, 2)

        # Dibujar sprites dinámicos
        for grupo in elementos:
            if isinstance(grupo, pygame.sprite.Group):
                grupo.draw(self.pantalla)
            elif isinstance(grupo, list):
                for e in grupo:
                    self.pantalla.blit(e.image, e.rect)
            else:
                self.pantalla.blit(grupo.image, grupo.rect)

        # Mostrar en pantalla
        pygame.display.flip()

    def init_view(self):
        self.dibujarFila()
        self.dibujarHuella()
        #dibujar pantalla agente
        pygame.draw.line(self.pantalla, BLACK, (657,0), (657,40), 5) 
        #dibujar cuadros con texto
        self.dibujarCuadroTexto("ENTRADA", GREEN,910, 650, 100, 40,3)
        self.dibujarCuadroTexto("SALIDA",RED,240,650,100,40,3)
        self.dibujarCuadroTexto("SALIDA",RED,1110,650,100,40,3)
        self.dibujarCuadroTexto("",BLACK,550,40,220,130,7)
        self.dibujarCuadroTexto("1",BLUE,150,65,30,30,2)
        self.dibujarCuadroTexto("2",BLUE,440,65,30,30,2)
        self.dibujarCuadroTexto("3",BLUE,850,65,30,30,2)
        self.dibujarCuadroTexto("4",BLUE,1140,65,30,30,2)

        
    def dibujarCuadroTexto(self, texto, color,x,y,ancho,largo,width):
        fuente = pygame.font.SysFont(None, 25)
        texto = fuente.render(texto, True, WHITE)
        cuadro = pygame.Rect(x,y,ancho,largo)
        pygame.draw.rect(self.pantalla, color, cuadro, width=width)
        texto_rect = texto.get_rect(center=cuadro.center)
        self.pantalla.blit(texto, texto_rect)

    def dibujarHuella(self):
        img_huella = pygame.image.load("resources/huellas.png").convert()
        img_huella.set_colorkey((0,0,0))
        self.pantalla.blit(img_huella, [655,377])
        self.pantalla.blit(img_huella, [655,477])
        self.pantalla.blit(img_huella, [805,480])
        self.pantalla.blit(img_huella, [955,475])
        self.pantalla.blit(img_huella, [955,575])

        self.pantalla.blit(img_huella, [115,270])
        self.pantalla.blit(img_huella, [450,270])
        self.pantalla.blit(img_huella, [870,270])
        self.pantalla.blit(img_huella, [1160,270])

    def dibujarFila(self):
        pygame.draw.line(self.pantalla, GRAY, (710,330), (710,430), 3) #1-4
        pygame.draw.line(self.pantalla, GRAY, (610,330), (610,530), 3) #2-3
        pygame.draw.line(self.pantalla, GRAY, (710,430), (1010,430), 3) #4-5
        pygame.draw.line(self.pantalla, GRAY, (610,530), (910,530), 3) #3-6
        pygame.draw.line(self.pantalla, GRAY, (1010,430), (1010,640), 3) #5-7
        pygame.draw.line(self.pantalla, GRAY, (910,530), (910,640), 3) #6-8