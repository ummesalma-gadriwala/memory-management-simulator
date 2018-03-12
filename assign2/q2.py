#import os
def main():
    length = 0
    lenLater = 0
    inputFile = open('output-corrected.txt','r')
    result = open('result.txt','r')
    #print(inputFile.readline())
    lineRead = inputFile.readline()
    for i in range(1000):
    #while (lineRead != ' '):
        length = length +1
            
        lineInput = lineRead
        lineInput = lineInput.split(' ')
        lineResult = result.readline()
        lineResult = lineResult.split(' ')
        # print(lineInput)
        #print(lineResult)
        virtualMemory = lineInput[2]
        virtualMemoryResult = lineResult[2]
        phyMem = lineInput[6]
        phyMemResult = lineResult[8]
        valIn = lineInput[7]
        valRes = lineResult[9]
        #print(valRes)
        #valRes = valRes[0:8]
        # print("V: ",virtualMemory, " R: ",virtualMemoryResult)
        # print("V: ",phyMem, " R: ",phyMemResult)
        #print("V: ",valIn, " R: ",valRes)
        if(virtualMemory == virtualMemoryResult):
            if(phyMem == phyMemResult):
                    if(valIn == valRes):
                        lenLater = lenLater + 1
                    else:
                        print(valIn, " ", valRes)
                       
        lineRead = inputFile.readline()
         
    #in result get rid of \n at the end
    print(length)
    print(lenLater)
    inputFile.close()
    result.close()
main()
    
