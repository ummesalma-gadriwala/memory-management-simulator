def main():
    #length = 0
    #lenLater = 0
    inputFile = open('output.txt','r')
    result = open('result.txt','r')

    lineRead = inputFile.readline()

    for i in result.readlines():
    	if i[0] in ('T', 'P'):
    		break
	r = i.split(' ')
	o = lineRead.split(' ')
	
	rVA = r[2]
	rPN = r[3][6:]
	rO = r[4][7:]
	rPA = r[8]
	rV = r[9][6:]
	
	oVA = o[2]
	oPN = o[3][6:]
	oO = o[4][7:]
	oPA = o[8]
	oV = o[9][6:]
	
	if not ((rVA == oVA) and (rPN == oPN) and (rO == oO) and (rPA == oPA) and (rV == oV)):
		print ("Result", rVA, rPN, rO, rPA, rV)
		print ("Output", oVA, oPN, oO, oPA, oV)
	
	lineRead = inputFile.readline()
	return

'''
    	lineRead = i
        length = length +1
            
        lineInput = lineRead
        lineInput = lineInput.split(' ')
        lineResult = result.readline()
        lineResult = lineResult.split(' ')
        #print(lineInput)
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
'''
main()
    
