import math
from matplotlib import pyplot as plt

G = 6.674

allPositions = {}

allPlanets = {
    "A": (0, 0, 40, [0, 0]),
    "B": (0, 10, 0.01, [5, 0]),
}

def magn(x, y):
    return math.sqrt(x**2 + y**2)

class Vector:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y

class Planet:
    def __init__(self, name, x, y, mass, vel) -> None:
        self.name = name
        self.x = x
        self.y = y
        self.mass = mass
        self.vel = vel

    def distTo(self, other):
        return magn(self.x - other.x, self.y - other.y)

class World:
    def __init__(self, planets) -> None:
        self.planets = planets
        self.tick = 0
        for p in planets:
            allPositions[p.name] = []

    def display(self):
        print(f"World state in T+{self.tick}")
        for p in self.planets:
            print(f"{p.name} : pos {round(p.x, 2)} {round(p.y, 2)} | mass = {p.mass} | vel = {p.vel}")
        print()

    def updatePlanetVel(self, p, other):
        d = p.distTo(other)
        f = G * ((p.mass * other.mass) / (d**2))
        weight = f / p.mass
        # if p.name == "B":
        #     print(round(d, 2), "|", round(weight, 2))

        fx = (other.x - p.x) / d * weight
        fy = (other.y - p.y) / d * weight

        p.vel[0] = p.vel[0] + fx
        p.vel[1] = p.vel[1] + fy

    def update(self):
        self.tick += 1
        # Update the planets' velocities
        for p in planets:
            for other in planets:
                if p.name != other.name:
                    self.updatePlanetVel(p, other)

        # Update the planets' positions
        for p in planets:
            p.x += p.vel[0]
            p.y += p.vel[1]
            allPositions[p.name].append((p.vel[0], p.vel[1]))

planets = []
for name in allPlanets.keys():
    p = Planet(name, allPlanets[name][0], allPlanets[name][1], allPlanets[name][2], allPlanets[name][3])
    planets.append(p)

plt.axis([-8, 8, -8, 8])
plt.title("simulation")

simulation = World(planets)
simulation.display()

steps = 1000
for i in range(steps):
    simulation.update()

for i, p in enumerate(allPositions["B"]):
    plt.plot(p[0], p[1], color=(i / steps, 0, 0), marker='.')

for i, p in enumerate(allPositions["A"]):
    plt.plot(p[0], p[1], color=[0, i / steps, 0], marker='.')


plt.grid()
plt.show()
