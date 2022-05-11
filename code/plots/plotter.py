import matplotlib.pyplot as plt 

def complex_multi_plot():
    f2=open("data/plot2.csv")
    f3=open("data/plot3.csv")
    f4=open("data/plot4.csv")


    x2=[]
    y2=[]
    for line in f2:
        data=[float(x) for x in line.split()]
        y2.append(calculate_balance(data[0],data[1]))
        x2.append(data[3])

    x3=[]
    y3=[]
    for line in f3:
        data=[float(x) for x in line.split()]
        y3.append(calculate_balance(data[0],data[1]))
        x3.append(data[3])

    x4=[]
    y4=[]
    for line in f4:
        data=[float(x) for x in line.split()]
        y4.append(calculate_balance(data[0],data[1]))
        x4.append(data[3])

    x=[]
    y=[]

    for i in range(len(x2)): # 0 to len(X2)-1
        x_avg=(x2[i]+x3[i]+x4[i])/3
        y_avg=(y2[i]+y3[i]+y4[i])/3
        print(x_avg,y_avg)
        x.append(x_avg)
        y.append(y_avg)
    
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

    f2.close()
    f3.close()
    f4.close()

def multi_graph_same_plot():
    f2=open("data/plot2.csv")
    f3=open("data/plot3.csv")
    f4=open("data/plot4.csv")


    x2=[]
    y2=[]
    for line in f2:
        data=[float(x) for x in line.split()]
        y2.append(calculate_balance(data[0],data[1]))
        x2.append(data[3])

    x3=[]
    y3=[]
    for line in f3:
        data=[float(x) for x in line.split()]
        y3.append(calculate_balance(data[0],data[1]))
        x3.append(data[3])

    x4=[]
    y4=[]
    for line in f4:
        data=[float(x) for x in line.split()]
        y4.append(calculate_balance(data[0],data[1]))
        x4.append(data[3])

    
    # plotting the points  
    plt.plot(x2, y2, 'b',marker='o', markerfacecolor='red', markersize=5) 
    plt.plot(x3, y3, 'y',marker='o', markerfacecolor='red', markersize=5) 
    plt.plot(x4, y4, 'k',marker='o', markerfacecolor='red', markersize=5) 
        
    # naming the x axis 
    plt.xlabel('Number of average processes per minor cycle (av)') 
    # naming the y axis 
    plt.ylabel('Balance') 
        
    # giving a title to my graph 
    # plt.title('Balance with growing av for MAXPV=4') 
        
    # function to show the plot 
    plt.show() 

    f2.close()
    f3.close()
    f4.close()

def simple_plot():
    # x axis values 
    # corresponding y axis values 
    print('Enter file name:')
    filename = input()
    
    f=open(filename)
    #extract data and print to screen
    x=[]
    y=[]
    for line in f:
        data=[float(x) for x in line.split()]
        y.append(calculate_balance(data[0],data[1]))
        x.append(data[3])

    f.close()
    
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
    plt.plot(x, y,'r',label='Path travelled by robot') 

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

    plt.plot(x,y_boundary_up, 'k', label='Walls')
    plt.plot(x,y_boundary_down, 'k') 
        
    # function to show the plot 
    plt.xticks([])
    plt.yticks([])
    plt.legend()
    plt.show() 

def plot_robot_simulation_2(x,y):
    # x axis values 
    # corresponding y axis values 
    
    # plotting the points  
    plt.plot(x, y,'r',label='Path travelled by robot') 
        # naming the x axis 
    # plt.xlabel('Distance traveled by robot in forward direction (units)') 

    x_len= len(x)
    y_boundary_up =[10] * 85
    y_boundary_down =[0] * 30
    
    i=0
    while (i<66):
        y_boundary_up.append(4)
        i=i+1

    i=0
    while (i<52):
        y_boundary_up.append(8)
        i=i+1

    i=0
    left_up= x_len-203
    while (i<left_up):
        y_boundary_up.append(5)
        i=i+1

    #done only from here
    i=0
    while (i<143):
        y_boundary_down.append(-10)
        i=i+1

    i=0
    while (i<30):
        y_boundary_down.append(-2)
        i=i+1
    
    i=0
    left_down=x_len-203
    while (i<left_down):
        y_boundary_down.append(3)
        i=i+1

    #200

    plt.plot(x,y_boundary_up, 'k', label='Walls')
    plt.plot(x,y_boundary_down, 'k') 
    # plt.plot(x,y_boundary_down, 'k',  linewidth=7) 
        
    # function to show the plot 
    plt.xticks([])
    plt.yticks([])
    plt.legend()
    plt.show() 

def plot_robot_battery_level(x,battery_levels):
    # plt.plot(x, battery_levels,'k',marker='o', markerfacecolor='red', markersize=5) 
    x_battery_good= x[:17]
    battery_good= battery_levels[:17]
    plt.plot(x_battery_good, battery_good,'k', label='Normal battery life') 

    x_warning = x[16:21]
    battery_warning = battery_levels[16:21]
    plt.plot(x_warning, battery_warning,'b', label='Charge soon warning')

    x_low = x[20:]
    battery_low = battery_levels[20:]
    plt.plot(x_low, battery_low,'r', label='Low battery critical warning')

    plt.xlabel('Distance traveled by robot in forward direction (units)')
    plt.ylabel('Battery level returned by battery_check()') 
    
    #logic to spearate graphs for battery_level <=30(red) and >30 (black)
    # function to show the plot 
    plt.legend()
    plt.show() 

def main():
    print("Choose your option:\n1-Balance Plot\n2-Simulation Plot\n")
    option = int(input())

    if (option == 1):
        print("Choose your option:\n1-Single MAXPV Plot\n2-Complex multi MAXPV Plot\n3-Complex multi graph same Plot\n")
        option_of_plot = int(input())
        if (option_of_plot == 1):
            simple_plot()
        elif (option_of_plot ==2):
            complex_multi_plot()
        elif (option_of_plot ==3):
            multi_graph_same_plot()
        else:
            print("Invalid Input!!")
            exit()

    elif (option == 2):
        print("Choose your option:\n1-Simple Simulation\n2-Complex Simulation\n3-Battery Plots\n")
        option_of_simulation = int(input())
        
        print('Enter file name:')
        filename = input()
        f=open(filename)

        if(option_of_simulation >0 and option_of_simulation <=2):
            #extract data and print to screen
            x=[]
            y=[]
            for line in f:
                data=[float(x) for x in line.split()]
                y.append(data[2])
                x.append(data[1])
            if(option_of_simulation ==1):
                plot_robot_simulation_1(x,y)
            elif (option_of_simulation ==2):
                plot_robot_simulation_2(x,y)
        elif (option_of_simulation ==3):
            x=[]
            battery_levels=[]
            for line in f:
                data=[float(x) for x in line.split()]
                battery_levels.append(data[1])
                x.append(data[0])
            plot_robot_battery_level(x,battery_levels)
        else:
            print("Invalid Input!!")
            f.close()
            exit()
        f.close()
    else:
        print("Invalid Input!!")
        exit()

main()