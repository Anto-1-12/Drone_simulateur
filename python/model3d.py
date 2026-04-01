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