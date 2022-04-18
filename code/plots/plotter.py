import matplotlib.pyplot as plt 

def plot_example():
    # x axis values 
    x = [1,2,3] 
    # corresponding y axis values 
    y = [2,4,1] 
        
    # plotting the points  
    plt.plot(x, y) 
        
    # naming the x axis 
    plt.xlabel('x - axis') 
    # naming the y axis 
    plt.ylabel('y - axis') 
        
    # giving a title to my graph 
    plt.title('My first graph!') 
        
    # function to show the plot 
    plt.show() 

def plot(x,y):
    # x axis values 
    # corresponding y axis values 
    
    # plotting the points  
    plt.plot(x, y) 
        
    # naming the x axis 
    plt.xlabel('x - axis') 
    # naming the y axis 
    plt.ylabel('y - axis') 
        
    # giving a title to my graph 
    plt.title('Balance with growing av') 
        
    # function to show the plot 
    plt.show() 

def calculate_balance(dirty: int, perfect: int) -> float:
    return dirty/perfect

def main():
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
    plot(x,y)

main()