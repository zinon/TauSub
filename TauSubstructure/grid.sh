#!/bin/bash
# localSetupPandaClient --noAthenaCheck

#setup
dry=false
local=false

case $local in
    (false)   type -P prun &>/dev/null && { echo "prun set"; } || { echo "prun is not set. Try: localSetupPandaClient --noAthenaCheck; voms-proxy-init -voms atlas "; return;}
    ;;
esac

RootVersion=5.34.10
Cmt=x86_64-slc6-gcc47-opt
nGBPerJob=MAX
nFilesPerJob=10
OutputRoot=tau4mom.root

touch datasets
while read input output;do #output should be smaller than 150-22 characters
    inputDS=$input
    outputDS=$output
    if [ -z "$inputDS" ] ; then
        echo 'Empty input ...'
        continue
    fi

    if $dry; then
        echo "dry run..."
        continue
    elif $local; then
        echo "running locally... "
        source RunAnalysis.sh
    else
        echo 'launching on grid... ' $submit for $inputDS, output=$outputDS
        prun --exec "echo %IN > inputfiles.txt; RunAnalysis.sh;" \
            --excludeFile=\plots,\Plotting,\illustrate,\results,\MakeClass,\tmp,\core.*,PrepareDatasets.*,\*.pdf,\*.png\*.log,\*.o,\*.so,\*.a,\*.d,\*.tmp,\*.dat,\*.tex,\*.svn,\*.table,\*.log,\*.txt,\*.root,\*.tgz,\*.tar,\*.gz,\*.*~ \
            --rootVer=$RootVersion \
            --cmtConfig=$Cmt \
            --outDS=$outputDS \
            --inDS=$inputDS \
            --outputs=$OutputRoot \
            --nFilesPerJob=$nFilesPerJob \
            --nGBPerJob=$nGBPerJob \
            --maxFileSize=5000000 \
	    --crossSite=200 
#            --mergeOutput \
#	    --memory=4096
#	    --excludedSite=UNI-FREIBURG
    fi

# 1GB = 1024 MB

#         --extFile=*.C, \
#  > prun/job.$outputDS.log 2>&1
#  > job.tmp 2>&1
# --site=NIKHEF-ELPROD_PHYS-HIGGS \
#--match="*NTUP_SUSY.*.root*"
#    --excludedSite=SFU-LCG2
#    --excludedSite=ANALY_ARC
#    --excludedSite=ANALY_SLAC
#    ANALY_ARC
#    --excludedSite=ANALY_TAIWAN, TAIWAN-LCG2

#    --excludedSite=TAIWAN-LCG2,ANALY_TAIWAN

   #--site=TRIUMF-LCG2_SCRATCHDISK

#   --excludedSite=ANALY_SFU,SFU-LCG2,ANALY_SFU_bugaboo,TAIWAN-LCG2,ANALY_TAIWAN

done < datasets

