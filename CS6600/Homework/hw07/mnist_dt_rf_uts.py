#/usr/bin/python

###########################################
# Unit Tests for Assignment 7
# bugs to vladimir kulyukin via canvas
###########################################

import random
import sys
import numpy as np
import unittest
from mnist_dt_rf import *

class mnist_dt_rf_uts(unittest.TestCase):

    # def test_ut01(self):
    #     ## let's create, fit, and validate a decision tree on MNIST.
    #     fit_validate_dt()


    def test_ut02(self):
        ### let's create ndts decision trees with random initial states
        ### and fit and validate them on MNIST.
        print("********************FIRST WE DO 5 RANDOM DT'S**********************")
        ndts = 5
        fit_validate_dts(5)
        print("********************TERMINUS 5 RANDOM DT'S**********************")

    # def test_ut03(self):
    #     ### let's create an RF with 5 trees, and fit and validate it on MNIST.
    #     fit_validate_rf(5)
       
    def test_ut04(self):
        ### let's create RF with 10, 20, 30, 40, and 50 trees, and fit and validate each on MNIST.
        print("********************Last part...MANY RFs **********************")
        low_nt, high_nt = 10, 500
        fit_validate_rfs(low_nt, high_nt)
        print("********************TERMINUSTERMINUS**********************")
    
if __name__ == '__main__':
    unittest.main()
    pass
