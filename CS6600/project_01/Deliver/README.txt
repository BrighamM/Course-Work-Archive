Hello, 
I hope this readme will help with grading my project1.

PLEASE NOTE
I did not use load_nets.py, I found that I did not need this file.

Everything that is needed is contained in the file: cs5600_6600_f20_project01_ensemble_uts.py

In the above named file (cs5600_6600_f20_project01_ensemble_uts) you can provide the location 
of the validation datasets that you will be using to grade my assignment. 

This can be accomplished by appropriately editing lines 39-49.
If you do this and provide the relative location of the validation datasets, then all you have 
to do to obtain the validation percentage report is run cs5600_6600_f20_project01_ensemble_uts.py
After about 12 minutes, you will get a report that looks similar to the following:

Bee1_Gray_Ann_Ensemble_Validation_Perc : 0.933390022675737
Bee2_1S_Gray_Ann_Ensemble_Validation_Perc : 0.6832360452389639
Bee4_Gray_Ann_Ensemble_Validation_Perc : 0.7849555335968379
Buzz1_Ann_Ensemble_Validation_Perc : 0.5852173913043478
Buzz2_Ann_Ensemble_Validation_Perc : 0.42333333333333334
Buzz3_Ann_Ensemble_Validation_Perc : 0.7183580387685291
Bee1_Cnn_Ensemble_Validation_Perc : 0.9739229024943311
Bee2_1S_Cnn_Ensemble_Validation_Perc : 0.7837468077344035
Bee4_Cnn_Ensemble_Validation_Perc : 0.737401185770751
Buzz1_Cnn_Ensemble_Validation_Perc : 0.5530434782608695
Buzz2_Cnn_Ensemble_Validation_Perc : 0.3616666666666667
Buzz3_Cnn_Ensemble_Validation_Perc : 0.6596351197263398

HOWEVER!
It was also requested to provide loaders for the ensembles.
This is done on lines: 251-313
And again on lines: 425-459

There was also a requirement:
"define predict_with_tfl_ensemble() that allows us to classify a single audio/image with your ensemble. 
We'll use this function to run your ensemble on our test dataset."
This function is defined on lines: 409-421
This function (predict_with_tfl_ensemble(ensemble, example, predict_fun)) is used in validateEnsembleTWO(someEnsemble, validationDir, predictorFunction)
which is located on line: 386


Please contact me if you have any questions or issues with my project.
As a side note each Ensemble contains 10 nets.