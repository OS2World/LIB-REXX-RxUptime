/* Example of RxUptime functions */
call RxFuncAdd 'RxLoadUptime','RxUptime','RxLoadUptime'
call RxLoadUptime

numeric digits 15

msCount=RxMSCount()

/* the following may not work on Warp 3 */
tmFreq=RxTmrFreq()
tmTime=RxTmrTime()

tmHi=word(tmTime,1)
tmLo=word(tmTime,2)

tmSeconds=((tmHi*2**32)+tmLo)/tmFreq
msSeconds=msCount/1000
diffSeconds=abs(msSeconds-tmSeconds)

tmDays=tmSeconds%86400
tmSeconds=tmSeconds//86400
msDays=msSeconds%86400
msSeconds=msSeconds//86400
diffDays=diffSeconds%86400
diffSeconds=diffSeconds//86400
tmHours=tmSeconds%3600
tmSeconds=tmSeconds//3600
msHours=msSeconds%3600
msSeconds=msSeconds//3600
diffHours=diffSeconds%3600
diffSeconds=diffSeconds//3600
tmMinutes=tmSeconds%60
tmSeconds=tmSeconds//60
msMinutes=msSeconds%60
msSeconds=msSeconds//60
diffMinutes=diffSeconds%60
diffSeconds=diffSeconds//60

msTString=right(msDays,4,'0')||':'||,
          right(msHours,2,'0')||':'||,
          right(msMinutes,2,'0')||':'||,
          right(format(msSeconds,,0),2,'0')
tmTString=right(tmDays,4,'0')||':'||,
          right(tmHours,2,'0')||':'||,
          right(tmMinutes,2,'0')||':'||,
          right(format(tmSeconds,,0),2,'0')
diffTString=right(diffDays,4,'0')||':'||,
            right(diffHours,2,'0')||':'||,
            right(diffMinutes,2,'0')||':'||,
            right(format(diffSeconds,,0),2,'0')

say ''
say center('System Uptime',78)
say ''
say center('MS Counter',26)||center('CPU Timer',26)||center('Discrepancy',26)
say ''
say center(msTString,26)||center(tmTString,26)||center(diffTString,26)

call RxDropUptime
