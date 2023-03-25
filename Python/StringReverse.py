class String:
    def __init__(self,inputData):
        self.strData = inputData

    def Reverse(self):
        self.strData = self.strData[::-1]

    def __str__(self):
        return self.strData

myString = String("Hello World!!!")
myString.Reverse()
print(myString)