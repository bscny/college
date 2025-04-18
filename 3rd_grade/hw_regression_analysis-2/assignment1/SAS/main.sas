data fev;
infile 'fevdata.txt' firstobs=2;
input age fev ht $ sex $ smoke $;
run;

proc reg data=fev;
model fev = age;
run;
