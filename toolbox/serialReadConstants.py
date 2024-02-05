readOnly = "1) Read Only"
writeOnly = "2) Write Only"
readAndWrite = "3) Read and Write"

serialOptions = [readOnly,writeOnly,readAndWrite]
writeOnlyIndex = 1
writeIndexes = [1,2]
readIndexes = [0,2]

printRead = "Print Data read to console"
graphRead = "Graph Data read"

serialReadOptions = [printRead,graphRead]

newLine = "NewLine"
carriageReturn = "CarriageReturn"
carriageReturnAndNewLine = "NewLine + Carriage Return"
noAppend = "None"
serialWriteOptions = [newLine,carriageReturn,carriageReturnAndNewLine,noAppend]
serialWriteAppendments = {newLine : '\n', carriageReturn: '\r', carriageReturnAndNewLine: '\r\n',noAppend: ''}

baudRate = [110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200, 128000]
counter = 1
samples = 50
pltPause = 0.0001

dataValues = []
ylimit = 1023 ##max value arduino signal
xlimit = samples
