10 rem factor
20 let p=8191
30 let k=3
40 if k>p/k then goto 110
50 let l=p/k
51 print l
53 let l=l*k
54 print l
55 if p>l then goto 90
56 print p;" ";l
60 print k;" ";
70 let p=p/k
80 goto 40
90 let k=k+2
100 goto 40
110 if p>1 then print p;" ";
120 print
130 end
