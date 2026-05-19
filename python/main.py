from Espace import Drone
from Communication import InitialisationConnection,Canalouvert,Transmission,FermetureCanal
import time
import json
import sys

class Camera:
    def __init__(self):
        pass

class Game :

    sceau=time.time()
    
    tpsmax=100

    def __init__(self):

        print("Lancement simulation")

        self.drone=Drone()

        #sélection du mode de contrôle
        try :

            mode=sys.argv[1]

            if mode=='Y':
                print('test mode automatique')
                self.mode="Auto"
            elif mode=='N':
                print('test mode manuel')
                InitialisationConnection()
                self.mode="Manuel"

        except:

            print('erreur de mode de contrôle')
            print('mode manuel par défaut')
            InitialisationConnection()
            self.mode="Manuel"

        self.run=True

    def loop(self):

        #code du mode auto
        if self.mode=='Auto':
            while self.run:
                print("Mode auto")
                if time.time()-self.sceau >= 1/60 :
                    #Tic de 1/60 de seconde
                    print('tic')

                    #Update Time
                    self.sceau=time.time()

                    #ici commandes auto

                    #Tick de mouvement drone
                    self.drone.tickdemouvement()

                    #Synchronisation Coordonnées Drone pour visualisation
                    Transmission(json.dumps(self.drone.getcoordonnées())+"\n")

                    #Synchronisation Angle Drone pour visualisation
                    #Transmission(json.dumps(self.drone.getcoordonnées())+"\n")

        #code du mode manuel
        else:
            while self.run:

                if time.time()-self.sceau >= 1/60 :

                    #Tic de 1/60 de seconde
                    print('tic')

                    #Update Time
                    self.sceau=time.time()

                    #Réceptions commandes client
                    cmdreçu=Canalouvert()
                    print(cmdreçu) 

                    #Tick de mouvement drone
                    self.drone.tickdemouvement(cmdreçu)

                    #Test Transmission
                    #Transmission(json.dumps({"cmd":"Hellow"})+ "\n")

                    #Synchronisation Coordonnées Drone
                    Transmission(json.dumps(self.drone.getcoordonnées())+"\n")

                    #Synchronisation Angle Drone
                    Transmission(json.dumps(self.drone.getangle())+"\n")
                    
game = Game()
game.loop()
FermetureCanal()
print("Fermeture Simulation")