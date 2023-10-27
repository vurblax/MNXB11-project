#!/bin/bash
# This code manuipulates weather SMHI dataset aand cleans it by deleting head information, dashes and semicolons
#with spaces to make it undestandable for C++. The final result is a raw data 1 csv file. 
#            
# Examples:
#        ./cleaner.sh ../datasets/smhi-opendata_1_52230_20231007_155448_Falsterbo.csv



###### Functions #######################################################

## usage
# this function takes no parameters and prints an error with the information on how to run this script.
usage(){
	echo "----"
	echo -e "  To call this script please use"
	echo -e "   $0 '<path>'"
	echo -e "  Example:"
    echo -e "   $0 '/git/MNXB11-project/datasets/smhi-opendata_1_52230_20231007_155448_Falsterbo.csv'"
	echo "----"
}

###### Functions END =##################################################


SMHIINPUT=$1

if [[ "x$SMHIINPUT" == 'x' ]]; then
   echo "Missing input file parameter, exiting"
   usage
   exit 1
fi


DATAFILE=$(basename $SMHIINPUT)


# T4.1 If $SMHIINPUT not empty
if [[ "x$SMHIINPUT" != "x" ]]; then
   # Check if the file is a directory, it should not be! Exit with error in case.
   if [[ -d $SMHIINPUT ]]; then
      echo -e "This script requires a data file and not a directory, exiting..."     
      exit 1
   fi
   # Copy the file in the current directory as original_$DATAFILE
   echo "Copying input file $SMHIINPUT to original_$DATAFILE"
   cp -a $SMHIINPUT ./original_$DATAFILE
fi 


if [[ $? != 0 ]]; then
   echo "Error downloading or copying file, maybe wrong command syntax? exiting...."
   usage
   exit 1
fi

# Start clean up process

echo "Finding the first line containing 'Datum'..."
STARTLINE=$(grep -n 'Datum' original_${DATAFILE} | cut -d':' -f 1)

STARTLINE=$(( $STARTLINE + 1 ))

echo "Removing the first $STARTLINE lines, result in clean1_${DATAFILE}"
tail -n +$STARTLINE original_${DATAFILE} > clean1_${DATAFILE}

echo "Selecting only relevant columns, result in clean2_${DATAFILE}"
cut -d';' -f 1,2,3,4,5 clean1_${DATAFILE} > clean2_${DATAFILE}

echo "Substituting the ; with spaces, result in rawdata_${DATAFILE}"
sed 's/;/ /g' clean2_${DATAFILE} > rawdata_${DATAFILE}

echo "Substituting the - with spaces, result in rawdata2_${DATAFILE}"
sed 's/-/ /g' rawdata_${DATAFILE} > rawdata2_${DATAFILE}

cat /dev/null > report_${DATAFILE}

echo "Writing filesizes summary to report_${DATAFILE}"
for csvfile in *.csv; do
    SIZE=`stat -c %s $csvfile`
    echo "   file $csvfile has size: $SIZE" >> report_${DATAFILE}
done

rm original_${DATAFILE}
rm clean1_${DATAFILE}
rm clean2_${DATAFILE}
rm report_${DATAFILE}
rm rawdata_${DATAFILE}