
def log(datos):
    file=open('datos.csv',a)
    for i in datos[0] :
        file.write(datos[0][x] + ';'+  datos[1][x])
    file.close()
