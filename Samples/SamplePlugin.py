import Source2Py

class SamplePlugin:
    def Load(self):
        Source2Py.Print("Hello world!")
    
    def Unload(self):
        Source2Py.Print("Goodbye world!")