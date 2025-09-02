import pygame 
from model.constantes import DARK_GRAY, BLACK, BLUE, GRAY, GREEN, RED, WHITE, BROWN, RED_DARK

class View:
    def __init__(self, ancho, largo):
        self.pantalla = pygame.display.set_mode((ancho, largo))
        self.mensajePantalla = ""  # Atributo para almacenar el mensaje a mostrar
        self.pantalla.fill(DARK_GRAY)
        self.init_view()
        pygame.display.set_caption("Simulación MAS Sala Conferencia")

    def dibujar(self, elementos):
        # Limpiar pantalla
        self.pantalla.fill((255, 255, 255))
        self.pantalla.fill(DARK_GRAY)
        alfombra = pygame.Rect(490, 0, 145, 560)
        pygame.draw.rect(self.pantalla, RED_DARK, alfombra)
        escenario = pygame.Rect(270, 590, 590, 110)
        pygame.draw.rect(self.pantalla, BROWN, escenario)
        img_proyector = pygame.image.load('resources/proyector.png')
        self.pantalla.blit(img_proyector, (480,610))
        #pygame.draw.rect(self.pantalla, color, cuadro, width=width)
        self.dibujarCuadroTexto("ENTRADA", WHITE, 1090, 0, 210, 700, 3)
        #self.dibujarCuadroTexto("SALIDA", RED, 240, 650, 100, 40, 3)
        #self.dibujarCuadroTexto("SALIDA", RED, 1110, 650, 100, 40, 3)
        # Aquí se dibuja el recuadro con el mensaje usando self.mensajePantalla.
        #self.dibujarCuadroTexto(self.mensajePantalla, BLACK, 550, 40, 220, 130, 7)

        # Dibujar sprites dinámicos
        for grupo in elementos:
            if isinstance(grupo, pygame.sprite.Group):
                grupo.draw(self.pantalla)
            elif isinstance(grupo, list):
                for e in grupo:
                    self.pantalla.blit(e.image, e.rect)
            else:
                self.pantalla.blit(grupo.image, grupo.rect)

        pygame.display.flip()

    def init_view(self):
        pygame.draw.line(self.pantalla, BLACK, (657, 0), (657, 40), 5)
        img_proyector = pygame.image.load('resources/proyector.png')
        self.pantalla.blit(img_proyector, (430,500))
        #self.dibujarCuadroTexto("ENTRADA", GREEN, 910, 650, 100, 40, 3)
        #self.dibujarCuadroTexto("SALIDA", RED, 1110, 650, 100, 40, 3)
        #self.dibujarCuadroTexto(self.mensajePantalla, BLACK, 550, 40, 220, 130, 7)

    def presentarPantalla(self, texto):
        # Simplemente actualiza el mensaje que se usará en el recuadro.
        self.mensajePantalla = texto

    def dibujarCuadroTexto(self, texto, color, x, y, ancho, largo, width):
        cuadro = pygame.Rect(x, y, ancho, largo)
        pygame.draw.rect(self.pantalla, WHITE, cuadro)
        pygame.draw.rect(self.pantalla, color, cuadro, width=width)
        fuente = pygame.font.SysFont(None, 25)
        # Para permitir múltiples líneas, dividimos el texto.
        lines = texto.split('\n')
        line_height = fuente.get_linesize()
        total_height = len(lines) * line_height
        # Calcula el punto de inicio para centrar verticalmente.
        y_offset = cuadro.top + (cuadro.height - total_height) // 2
        for linea in lines:
            rendered_line = fuente.render(linea, True, color)
            text_rect = rendered_line.get_rect(centerx=cuadro.centerx, y=y_offset)
            self.pantalla.blit(rendered_line, text_rect)
            y_offset += line_height
