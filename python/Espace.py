# Rappel Coordonnées (X,Y,Z) = index[0,1,2] centregravité==0 alors explosion
# Rappel Orientation:
#https://www.drone-normandie.com/forces-aerodynamiques/
#https://dronetech-18.webself.net/les-forces

#Cravité:
G=9.8
P=G*0.8
#pas sûr de ça
import numpy as np
"""""
import Projection3D
class Model3D:
    def __init__(self,model,coo,size):

        self.size = size
        self.model = model

        self.coo = coo

        self.v = []
        self.vn = []
        self.f = []
        self.f_vn = []

        self.init_model()

        self.current_v = self.v
        self.current_vn = self.vn

        self.current_rotation = [0, 0, 0]
        self.rotate_model(self.current_rotation)

    def rotate_model(self,rotation):
        new_v = []
        for v in self.v:
            new_v.append(Projection3D.rotate_point(v,rotation))

        new_v2 = []
        for v2 in new_v:
            new_v2.append([v2[0] * self.size + self.coo[0],v2[1] * self.size + self.coo[1],v2[2] * self.size + self.coo[2]])
        self.current_v = new_v2

        new_vn = []
        for vn in self.vn:
            new_vn.append(Projection3D.rotate_point(vn,rotation))
        self.current_vn = new_vn

        self.current_rotation = rotation

    def init_model(self):
        with open(self.model,"r") as file:
            for line in file:
                parties = line.split()

                if not parties:
                    continue
                    
                if parties[0] == "v":
                    parties.pop(0)
                    self.v.append([float(parties[0]),-float(parties[2]),float(parties[1])])

                elif parties[0] == "vn":
                    parties.pop(0)
                    self.vn.append([float(parties[0]),-float(parties[2]),float(parties[1])])

                elif parties[0] == "f":
                    parties.pop(0)
                    f = []
                    f_vn = []
                    for p in parties:
                        f.append(int(p.split("/")[0])-1)
                        f_vn.append(int(p.split("/")[2])-1)

                    self.f.append(f)
                    self.f_vn.append(f_vn)
"""""

class Obstacle:
    def __init__(self):
        pass

class Eclairage:
    def __init__(self):
        pass

class Drone:
    #gravité à mettre ici
    Gravité=[0,
             -0.1, #-1
             0]
    #Vecteur momentum :
    Momentum=[0, #1
              0,
              0]

    def __init__(self):
        self.centregravité=[1,1,1]  # X droite gauche, Y hauteur, Z Profondeur
        self.orientation=[1,1,1]
        #positions des coins dans la liste
        # 0     1
        #   | |
        #   | |
        # 2     3
        self.coinsnumpy = np.array([
            [-10, 0, 10],
            [10, 0, 10],
            [-10, -0, 10],
            [10, -0, 10],
        ], dtype=float)
        self.coins=[[-10,0,10],[10,0,10],[-10,-0,10],[10,-0,10]]
        self.moteurs=[]*(4)
        for x in range(len(self.moteurs)):
            self.moteurs[x]=Moteur.__init__(self.coins[x],self.orientation)

    def tickdemouvement(self,commande): #+interprétation commandes
        try: 
            if commande['cmd']=="avancer":
                self.centregravité=[x,y+1,z]
                print('avancer')

            if commande['cmd']=="reculer":
                self.centregravité=[x,y-1,z]
                print('reculer')

            if commande['cmd']=="droite":
                self.centregravité=[x+1,y,z]
                print('droite')

            if commande['cmd']=="gauche":
                self.centregravité=[x-1,y,z]
                print('gauche')
            
        except:
            pass
        self.cravité()
        self.momentum()
        self.MinHauteur()

    def cravité(self):
        self.centregravité = [centre_elt + grav_elt for grav_elt, centre_elt in zip(self.Gravité, self.centregravité)]
        print(self.centregravité)

    def momentum(self):
        self.centregravité = [centre_elt + mome_elt for mome_elt, centre_elt in zip(self.Momentum, self.centregravité)]
        print(self.centregravité)

    def MinHauteur(self):
        if self.centregravité[1]<0:
            self.centregravité[1] += 10 

    #Ci-dessous : fonction d'angles
    def rotation_x(angle):
        c, s = np.cos(angle), np.sin(angle)
        return np.array([
            [1, 0, 0],
            [0, c,-s],
            [0, s, c]
        ])
    def rotation_y(angle):
        c, s = np.cos(angle), np.sin(angle)
        return np.array([
            [ c, 0, s],
            [ 0, 1, 0],
            [-s, 0, c]
        ])
    def rotation_z(angle):
        c, s = np.cos(angle), np.sin(angle)
        return np.array([
            [c,-s, 0],
            [s, c, 0],
            [0, 0, 1]
        ])
    
    def rotation_matrix(self,rx, ry, rz):
        return self.rotation_z(rz) @ self.rotation_y(ry) @ self.rotation_x(rx)

    def transform_cube(self,vertices, center, angles, scale=1.0):
        # angles = (rx, ry, rz)
        R = self.rotation_matrix(*angles)
        scaled = vertices * scale
        rotated = scaled @ R.T
        translated = rotated + center
        return translated  
    
    def getcoordonnées(self):
        return({
        "cmd":"sync_drone_pos",
        "x":self.centregravité[0],
        "y":self.centregravité[1],
        "z":self.centregravité[2]
    })
    def getangle(self):
        return({
        "cmd":"sync_drone_pos",
        "x":self.centregravité[0],
        "y":self.centregravité[1],
        "z":self.centregravité[2]
    })




class Moteur:
    #N=4?
    def __init__(self,position,orientation):
        self.vecteurdirection=[]
        self.position=position
        self.orientation=orientation

    def ON(Haut,Devant,Derrière,Gauche,Droite):
        pass

    def update_position_moteurs():
        pass

#tests
D=Drone()
D.cravité()
#https://rcdrone.top/fr/blogs/articles-fr/fpv-compute-thrust-to-weight?srsltid=AfmBOor1xA7qPBdZnOOoxTh3var7Lr_gRJ9PqXd6E7bw_4Sq1dtM0-1Q

"""""
Poussé en N pour chaque moteur pour un drone de 800g avec 4 moteurs (just pour etre en stationnaire)
P = m⋅g
  = 0,8x9,81
  = 7,85N
  = 7,85/4
  ≈ 1,96N
Il faut idealement avoir 3 fois cette force par moteur pour que le drone vol correctement donc :
    7,85x3 ≈ 23,5N

    Donc Min par moteur:
      = 4N
    Max : 
      = 6N
"""""

