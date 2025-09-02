import pygame
from model.constantes import ESTADOS_ALFOMBRA

class SpritePersona(pygame.sprite.Sprite):
    def __init__(self, *groups):
        super().__init__(*groups)
        self.sentado = False
        self.image = pygame.image.load(f"resources/{'sentada' if self.sentado else 'persona'}.png").convert_alpha()

        # Punto de entrada (la posición desde la que parte)
        self.pos_x, self.pos_y = 535, 0  
        self.rect = self.image.get_rect(topleft=(self.pos_x, self.pos_y))
        
        # Para saber en qué posición de la fila se encuentra
        self.index_cola = 0  
        self.sentado = False
        
        # Variables para la gestión del movimiento
        self.destinos = []          # Secuencia de posiciones (ruta) que deberá seguir
        self.destino_actual = None  # El destino inmediato (se actualizará cuando se llegue a él)
        self.velocidad = 0.6
        
        # Indica si la persona ya se encuentra en la ventanilla
        self.en_ventanilla = False  

    def actualizar_destino(self, lista_destinos):
        """
        Recibe una lista de destinos, la convierte en tuplas y asigna el primero como destino inmediato.
        Por ejemplo, al generar la persona se le puede pasar [ESTADOS_FILA[0]]
        y posteriormente cuando avance en la fila se actualizará con la siguiente posición.
        """
        self.destinos = [tuple(dest) for dest in lista_destinos]
        if self.destinos:
            self.destino_actual = self.destinos.pop(0)
        else:
            self.destino_actual = None

    def mover_hacia_destino(self):
        """
        Mueve la persona hacia el destino actual. 
        Si se alcanza la posición actual, se actualiza al siguiente destino (si existe).
        """
        if not self.destino_actual:
            return  # No hay destino asignado; la persona queda en reposo.
        
        dx, dy = self.destino_actual
        dir_x = dx - self.pos_x
        dir_y = dy - self.pos_y
        distancia = (dir_x ** 2 + dir_y ** 2) ** 0.5

        if distancia <= self.velocidad:
            # Se alcanza el destino actual
            self.pos_x, self.pos_y = dx, dy
            self.rect.topleft = (int(self.pos_x), int(self.pos_y))
            
            # Si hay más destinos pendientes (por ejemplo, avanzando en la fila), se asigna el siguiente.
            if self.destinos:
                self.destino_actual = self.destinos.pop(0)
            else:
                self.destino_actual = None
        else:
            # Movimiento gradual hacia el destino
            paso_x = self.velocidad * dir_x / distancia
            paso_y = self.velocidad * dir_y / distancia
            self.pos_x += paso_x
            self.pos_y += paso_y
            self.rect.topleft = (int(self.pos_x), int(self.pos_y))

    def llego_al_destino(self):
        """
        Retorna True si la persona ha alcanzado el último destino asignado.
        Esto permite que el controlador sepa cuándo actualizar la posición (por ejemplo, para avanzar en la fila).
        """
        return self.destino_actual is None

    def esta_sentada(self):
        return self.sentado

    def update(self):
        self.mover_hacia_destino()

        if hasattr(self, 'destino_fila') and self.destino_actual == self.destino_fila and not hasattr(self, 'en_asiento'):
            self.actualizar_destino([self.destino_final])
            self.en_asiento = True
