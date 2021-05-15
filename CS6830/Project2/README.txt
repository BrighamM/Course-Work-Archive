Dataset Source: https://data.world/dash/austin-crime-report-2015


The crimes listed are crimes reported and include a column titled "clearance_status". 
This attribute has three possible values:

C=Cleared by Arrest
O=Cleared by Exception (e.g. offender was killed, victim refuses to cooperate, extradition issues, etc.)
N=Not cleared


A few notes:

There are 43 columns. Not all of them show up when you display the table, so be sure to take a look at the ones that aren't visible!
Many of the columns are in percentage or dollar amounts and have the percent sign or dollar sign attached to them. In order to use these values as numbers do something similar to the following conversion:

dataset['colname'] = dataset['colname'].str.replace('$', '').astype('float')