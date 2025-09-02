import pygame 
from view.SpriteVentanilla import SpriteVentanilla
from model.constantes import DARK_GRAY,BLACK,BLUE,GRAY,GREEN,RED,WHITE

class View:
    def __init__(self, ancho, largo):
        self.pantalla = pygame.display.set_mode((ancho, largo))
        self.pantalla.fill(DARK_GRAY)
        #self.ventanillas = self.crearVentanillas(ventanillas)
        self.init_view()
        pygame.display.set_caption("Simulación de Agente Bancario")

    def dibujar (self, elementos):
        for elemento in elementos:
            self.pantalla.blit(elemento.image, elemento.rect)
        pygame.display.flip()
    
    def init_view(self):
        self.dibujarFila()
        #self.dibujarHuella()
        #self.dibujar(self.ventanillas)
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

    '''  
    def crearVentanillas(self, ventanillas):
        return [SpriteVentanilla(ventanillas[0],(95,110)),
                       SpriteVentanilla(ventanillas[1],(385,110)),
                       SpriteVentanilla(ventanillas[2],(800,110)),
                       SpriteVentanilla(ventanillas[3],(1090,110))]
    '''
        
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