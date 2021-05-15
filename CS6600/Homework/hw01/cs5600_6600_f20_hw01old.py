
####################################################
# CS 5600/6600: F20: Assignment 1
# YOUR NAME
# YOUR A#
#####################################################

import numpy as np

class and_percep:

    def __init__(self):
        ## your code
        self.biasVal = -1
        self.weightOne = .51
        self.weightTwo = .51
        pass
        
    def output(self, x):
        ## your code
        result = x[0]*self.weightOne + x[1]*self.weightTwo
        if result + self.biasVal > 0:
            return 1
        else:
            return 0
        pass

class or_percep:
    
    def __init__(self):
        ## your code
        self.biasVal = -1
        self.weightOne = 1.01
        self.weightTwo = 1.01
        pass

    def output(self, x):
        ## your code
        result = x[0]*self.weightOne + x[1]*self.weightTwo
        if result + self.biasVal > 0:
            return 1
        else:
            return 0
        pass

class not_percep:
    
    def __init__(self):
        ## your code
        self.biasVal = -1
        self.weightVal = 1.01
        pass

    def output(self, x):
        ## your code
        result = x[0]*self.weightVal
        if result + self.biasVal > 0:
            return 0
        else:
            return 1
        pass

class xor_percep:
    
    def __init__(self):
        ## your code
        self.andP = and_percep()
        self.orP = or_percep()
        self.notP = not_percep()

        pass

    def output(self, x):
        ## your code
        and1Result = self.andP.output(np.array([int(x[0]), int(x[1])]))
        orResult = self.orP.output(np.array([int(x[0]), int(x[1])]))
        notResult = self.notP.output(np.array([int(and1Result)]))        
        return self.andP.output(np.array([int(orResult), int(notResult)]))
        pass

class xor_percep2:
    def __init__(self):
        ## your code
        self.bias = -1
        self.weightx000 = .51
        self.weightx001 = 1.01
        self.weightx010 = .51
        self.weightx011 = 1.01
        self.weightx10 = -1.5
        self.weightx11 = 1.01
        pass

    def threshold(self, x):
        ## your code
        pass
    
    def output(self, x):
        ## your code
        x0 = x[0]
        x1 = x[1]
        resultX0 = x0*self.weightx000 + x1*self.weightx010 + self.bias
        resultX1 = x0*self.weightx001 + x1*self.weightx011 + self.bias
        resultX0 = 1 if resultX0 > 0 else 0
        resultX1 = 1 if resultX1 > 0 else 0

        finResult = resultX0*self.weightx10 + resultX1*self.weightx11 + self.bias
        finResult = 1 if finResult > 0 else 0 
        return np.array([int(finResult)])
        pass

class percep_net:
    
    def __init__(self):
        ## your code
        self.orP = or_percep()
        self.andP = and_percep()
        self.notP = not_percep()

        pass

    def output(self, x):
        ## your code
        or1Result = self.orP.output(np.array([int(x[0]), int(x[1])]))
        notResult = self.notP.output(np.array([int(x[2])]))
        andResult = self.andP.output(np.array([int(or1Result), int(notResult)]))
        or2Result = self.orP.output(np.array([int(andResult), int(x[3])]))
        return or2Result
        pass

    
        





