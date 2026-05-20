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
             -3, #-1 pour test, -7.84 N pour un drone de 800 grammes
             0]
    #Vecteur momentum :
   

    def __init__(self):
        self.Momentum=[0, #1 pour test
            0,
            0]
        
        self.centregravité=[1,1,1]  # coordonnées, X droite gauche, Y hauteur, Z Profondeur*

        self.orientationdegrés=[0,0,0]

        self.orientation=[0,0,1]    #vecteur orientation, X Roulis, Y Tangage, Z Lacet https://fr.wikipedia.org/wiki/Axes_de_rotation_d%27un_a%C3%A9ronef

        self.orientationmoteur=[0,1,0] #vecteur poussée,

        self.puissance=6  # max 23,5N, hover +7.84N,

        self.pourcentmoteur=0 

        self.hover=False

        #positions des coins dans la liste
        # 0     1
        #   | |
        #   | |
        # 2     3
        #annulé
        self.coins=[[-10,0,10],[10,0,10],[-10,-0,10],[10,-0,10]]
        self.moteurs=[]*(4)
        for x in range(len(self.moteurs)):
            self.moteurs[x]=Moteur.__init__(self.coins[x],self.orientation)

    def tickdemouvement(self,commandes): #+interprétation commandes 
        for Ordre in commandes:
            # angles de rotation autour des axes = (rx, ry, rz)
            #Tangage
            if Ordre['cmd']=="avancer":
                if self.orientationdegrés[0]<360:
                    self.orientationdegrés[0]+=1
                else: 
                    self.orientationdegrés[0]=0
                print('avancer')
            if Ordre['cmd']=="reculer":
                if self.orientationdegrés[0]>0 :
                    self.orientationdegrés[0]-=1
                else: 
                    self.orientationdegrés[0]=360
                
                print('reculer')

            #Lacet
            if Ordre['cmd']=="tourneràdroite":
                if self.orientationdegrés[1]<360:
                    self.orientationdegrés[1]+=1
                else: 
                    self.orientationdegrés[1]=0
                print('tourneràdroite')
            if Ordre['cmd']=="tourneràgauche":
                if self.orientationdegrés[1]>0 :
                    self.orientationdegrés[1]-=1
                else: 
                    self.orientationdegrés[1]=360
                print('tourneràgauche')

            #Roulis
            if Ordre['cmd']=="rolldroite":
                if self.orientationdegrés[2]<360:
                    self.orientationdegrés[2]+=1
                print('rolldroite')
            if Ordre['cmd']=="rollgauche":
                if self.orientationdegrés[2]>0 :
                    self.orientationdegrés[2]-=1
                else: 
                    self.orientationdegrés[2]=360
                print('rollgauche')

            #gestionpuissance
            if Ordre['cmd']=="augmenter puissance moteur":
                if self.pourcentmoteur<100 and not self.hover:
                    self.pourcentmoteur+=5
            if Ordre['cmd']=="diminuer puissance moteur":
                if self.pourcentmoteur>0 and not self.hover:
                    self.pourcentmoteur-=5
            if Ordre['cmd']=="hover":
                if self.hover==False:
                    self.memoire=self.pourcentmoteur
                    self.pourcentmoteur=50
                    self.hover=True
                else:
                    self.pourcentmoteur=self.memoire
                    self.hover=False

        self.cravité()
        self.momentum()
        self.MinHauteur()

    def cravité(self):
        self.centregravité = [centre_elt + grav_elt for grav_elt, centre_elt in zip(self.Gravité, self.centregravité)]

    def momentum(self):
        self.poussée()
        print("self.puissance")
        print(self.puissance)
        print(self.pourcentmoteur)
        print("self.Momentum")
        print(self.Momentum)
        self.centregravité = [centre_elt + mome_elt for mome_elt, centre_elt in zip(self.Momentum, self.centregravité)]
        print("self.centregravité")
        print(self.centregravité)
        print("self.orientationdegrés")
        print(self.orientationdegrés)

    def MinHauteur(self):
        if self.centregravité[1]<0:
            self.centregravité[1] = 0 

    def poussée(self):

        matricerotation = self.rotation_matrix(
        self.orientationdegrés[0],
        self.orientationdegrés[1],
        self.orientationdegrés[2]
    )

        self.v_initial=np.array([0,1,0])
        
        v_direction = matricerotation @ self.v_initial
        v_direction=v_direction.tolist()

        print("v_direction")
        print(v_direction)

        force = round(self.puissance * self.pourcentmoteur / 100, 2)

        self.Momentum = [
        v_direction[0] * force,
        v_direction[1] * force,
        v_direction[2] * force
    ]

    #Ci-dessous : fonction d'angles

    def rotation_x(self,angle):
        c = round(np.cos(angle),12)
        s = round(np.sin(angle),12)
        return np.array([
            [1, 0, 0],
            [0, c,-s],
            [0, s, c]
        ])
    def rotation_y(self,angle):
        c = round(np.cos(angle),12)
        s = round(np.sin(angle),12)
        return np.array([
            [ c, 0, s],
            [ 0, 1, 0],
            [-s, 0, c]
        ])
    def rotation_z(self,angle):
        c = round(np.cos(angle),12)
        s = round(np.sin(angle),12)
        return np.array([
            [c,-s, 0],
            [s, c, 0],
            [0, 0, 1]
        ])
    
    def rotation_matrix(self,rx, ry, rz):
        #conversion degrés en radians 
        rx=np.radians(rx)
        ry=np.radians(ry)
        rz=np.radians(rz)
        return self.rotation_z(rz) @ self.rotation_y(ry) @ self.rotation_x(rx)
    

    #inutile
    def changerorientation(self,angles): #
        # angles de rotation autour des axes = (rx, ry, rz)
        Rotation=self.rotation_matrix(angles[0],angles[1],angles[2])
        résultatdrone=Rotation@self.orientation
        self.orientation=résultatdrone
    #inutile
    def changerorientationmoteur(self,angles): #
        # angles de rotation autour des axes = (rx, ry, rz)
        Rotation=self.rotation_matrix(angles[0],angles[1],angles[2])
        résultatmoteur=Rotation@self.orientationmoteur
        self.orientationmoteur=résultatmoteur

    #fonctions de partage des données
    def getcoordonnées(self):
        return({
        "cmd":"sync_drone_pos",
        "x":float(self.centregravité[0]),
        "y":float(self.centregravité[1]),
        "z":float(self.centregravité[2])
    })
    def getangle(self):
        return({
        "cmd":"sync_drone_ang",
        "x":float(self.orientationdegrés[0]),
        "y":float(self.orientationdegrés[1]),
        "z":float(self.orientationdegrés[2]),
        "x2":float(self.orientationmoteur[0]),
        "y2":float(self.orientationmoteur[1]),
        "z2":float(self.orientationmoteur[2]),
    })



class Moteur:
    
    def __init__(self,position,orientation):
        self.position=position
        self.orientation=orientation
        self.force=0 # en pourcent ex: 0.8

    def ON(self,Force):
        self.force=Force

    def OFF(self):
        self.force=0

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

