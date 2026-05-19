import numpy as np
class d3:

    def __init__(self):
        self.orientation=[0, #x
                          0, #y
                          0] #z

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
        #tests
        #"""""
        print(self.rotation_z(np.radians(rz)))
        print(self.rotation_y(np.radians(ry)))
        print(self.rotation_x(np.radians(rx)))
        #"""""
        #conversion degrés en radians 
        rx=np.radians(rx)
        ry=np.radians(ry)
        rz=np.radians(rz)
        return self.rotation_z(rz) @ self.rotation_y(ry) @ self.rotation_x(rx)
    
    def transformation(self,angles):
        # angles = (rx, ry, rz)
        Rotation=self.rotation_matrix(angles[0],angles[1],angles[2])
        print(Rotation)
        v=np.array([1,0,0])
        résultat=v@Rotation@self.orientation
        print("résultat")
        print(résultat)
          
dr=d3()
dr.transformation([0,0,90])

"""""
original
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
"""""