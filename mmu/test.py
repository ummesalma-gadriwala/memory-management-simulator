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
main()
    
