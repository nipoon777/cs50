import cs50

while True:
    print("Height: ",end=" ")
    height = cs50.get_int()
    if height>0 or height < 24 :
        break


for i in range(height):
    print(" "*(height-i),end=" ")
    print("#"*(i+1))





