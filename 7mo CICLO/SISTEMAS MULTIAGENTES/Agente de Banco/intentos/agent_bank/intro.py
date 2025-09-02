import pygame
import random

pygame.init()

# Configuración de pantalla
WIDTH, HEIGHT = 900, 600
SCREEN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Simulación Agencia Bancaria")
FPS = 60
clock = pygame.time.Clock()

# Colores
WHITE = (255, 255, 255)
BLUE = (50, 100, 255)
RED = (255, 50, 50)
GRAY = (200, 200, 200)
BLACK = (0, 0, 0)

# Clase Persona
class Persona:
    def __init__(self, especial=False, turno=0):
        self.especial = especial
        self.color = RED if especial else BLUE
        self.tiempo_atencion = random.randint(8, 14) * FPS  # Atención más lenta
        self.atendida = False
        self.moviendo = False
        self.x = 100
        self.y = HEIGHT - 50
        self.target_x = self.x
        self.target_y = self.y
        self.turno = turno

    def mover_a(self, x, y):
        self.target_x = x
        self.target_y = y
        self.moviendo = True

    def actualizar_posicion(self):
        if self.moviendo:
            dx = self.target_x - self.x
            dy = self.target_y - self.y
            velocidad = 3
            if abs(dx) < velocidad and abs(dy) < velocidad:
                self.x, self.y = self.target_x, self.target_y
                self.moviendo = False
            else:
                if dx != 0:
                    self.x += velocidad if dx > 0 else -velocidad
                if dy != 0:
                    self.y += velocidad if dy > 0 else -velocidad

    def dibujar(self, surface, fuente):
        pygame.draw.circle(surface, self.color, (int(self.x), int(self.y)), 15)
        texto = fuente.render(str(self.turno), True, BLACK)
        surface.blit(texto, (int(self.x) - 5, int(self.y) - 10))

# Clase Ventanilla
class Ventanilla:
    def __init__(self, x):
        self.x = x
        self.y = 100
        self.ocupada = False
        self.persona = None
        self.tiempo_restante = 0

    def atender(self, persona):
        self.persona = persona
        self.ocupada = True
        self.tiempo_restante = persona.tiempo_atencion
        persona.atendida = True
        persona.mover_a(self.x + 50, self.y + 50)

    def actualizar(self):
        if self.ocupada:
            self.tiempo_restante -= 1
            if self.tiempo_restante <= 0:
                self.ocupada = False
                self.persona = None

    def dibujar(self, surface):
        pygame.draw.rect(surface, GRAY, (self.x, self.y, 100, 100))
        if self.persona:
            self.persona.dibujar(surface, pygame.font.SysFont(None, 18))

# Inicialización
ventanillas = [Ventanilla(150 + i * 180) for i in range(4)]
fila = []
personas = []
contador_turnos = 1
tiempo_generacion = 0

# Main loop
running = True
while running:
    clock.tick(FPS)
    SCREEN.fill(WHITE)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Generar personas más seguido
    tiempo_generacion += 1
    if tiempo_generacion > 1 * FPS:
        especial = random.random() < 0.3
        persona = Persona(especial, turno=contador_turnos)
        contador_turnos += 1
        fila.append(persona)
        personas.append(persona)
        tiempo_generacion = 0

    # Actualizar ventanillas
    for vent in ventanillas:
        vent.actualizar()

    # Atender personas (prioridad especial)
    for vent in ventanillas:
        if not vent.ocupada:
            especial = next((p for p in fila if p.especial and not p.atendida), None)
            if especial:
                fila.remove(especial)
                vent.atender(especial)
            elif fila:
                normal = fila.pop(0)
                vent.atender(normal)

    # Reorganizar la fila (mover cada uno a su nueva posición)
    for i, persona in enumerate(fila):
        target_y = HEIGHT - 50 - i * 40
        persona.mover_a(100, target_y)

    # Actualizar y dibujar personas
    fuente = pygame.font.SysFont(None, 24)
    for p in personas:
        p.actualizar_posicion()
        if not p.atendida:
            p.dibujar(SCREEN, fuente)

    # Dibujar ventanillas
    for vent in ventanillas:
        vent.dibujar(SCREEN)

    # Texto de estado
    texto = fuente.render(f"Personas en fila: {len(fila)}", True, BLACK)
    SCREEN.blit(texto, (20, 20))

    pygame.display.flip()

pygame.quit()