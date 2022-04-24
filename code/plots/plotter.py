import matplotlib.pyplot as plt 

def plot(x,y):
    # x axis values 
    # corresponding y axis values 
    
    # plotting the points  
    plt.plot(x, y,marker='o', markerfacecolor='red', markersize=5) 
        
    # naming the x axis 
    plt.xlabel('Number of average processes per minor cycle (av)') 
    # naming the y axis 
    plt.ylabel('Balance') 
        
    # giving a title to my graph 
    # plt.title('Balance with growing av for MAXPV=4') 
        
    # function to show the plot 
    plt.show() 

def calculate_balance(dirty: int, perfect: int) -> float:
    return dirty/perfect

def plot_robot_simulation_1(x,y):
    # x axis values 
    # corresponding y axis values 
    
    # plotting the points  
    plt.plot(x, y,'r') 

    x_len= len(x)
    y_boundary_up =[10] * x_len
    y_boundary_down =[0] * 30
    
    i=0
    
    while (i<55):
        y_boundary_down.append(-10)
        i=i+1

    i=0

    left=x_len-85

    while (i<left):
        y_boundary_down.append(0)
        i=i+1

    plt.plot(x,y_boundary_up, 'k')
    plt.plot(x,y_boundary_down, 'k') 
        
    # function to show the plot 
    plt.show() 

def plot_robot_simulation_2(x,y):
    # x axis values 
    # corresponding y axis values 
    
    # plotting the points  
    plt.plot(x, y,'r', linewidth=4) 

    x_len= len(x)
    y_boundary_up =[10] * 85
    y_boundary_down =[0] * 30
    
    i=0

    while (i<36):
        y_boundary_up.append(4)
        i=i+1

    
    i=0
    while (i<91):
        y_boundary_down.append(-10)
        i=i+1


    plt.plot(x,y_boundary_up, 'k', linewidth=10)
    plt.plot(x,y_boundary_down, 'k',  linewidth=10) 
        
    # function to show the plot 
    plt.xticks([])
    plt.yticks([])
    plt.show() 

def main():
    print('Enter file name:')
    filename = input()

    print("Choose your option:\n1-Balance Plot\n2-Simulation Plot\n")
    option = int(input())

    if (option == 1):
        f=open(filename)
        #extract data and print to screen
        x=[]
        y=[]
        for line in f:
            data=[float(x) for x in line.split()]
            y.append(calculate_balance(data[0],data[1]))
            x.append(data[3])

        f.close()
        plot(x,y)
    elif (option == 2):
        print("Choose your option:\n1-Simple Simulation\n2-Complex Simulation\n")
        option_of_simulation = int(input())
        f=open(filename)
        #extract data and print to screen
        x=[]
        y=[]
        for line in f:
            data=[float(x) for x in line.split()]
            y.append(data[2])
            x.append(data[1])

        f.close()
        if(option_of_simulation ==1):
            plot_robot_simulation_1(x,y)
        elif (option_of_simulation ==2):
            plot_robot_simulation_2(x,y)
        else:
            print("Invalid Input!!")
            exit()
    else:
        print("Invalid Input!!")
        exit()

main()