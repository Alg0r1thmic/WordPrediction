import codecs

v1 = set();
v2 = set();
v3 = set();
v4 = set();
v5 = set();
v6 = set();
v7 = set();
v8 = set();
v9 = set();
v10 = set();
v11 = set();
v12 = set();
v13 = set();
v14 = set();
v15 = set();

for line in codecs.open("../sets/extra_features.csv","r","utf8"):
	a = line.split(",")
	v1.add(a[1]);
	v2.add(a[2]);
	v3.add(a[3]);
	v4.add(a[4]);
	v5.add(a[5]);
	v6.add(a[6]);
	v7.add(a[7]);
	v8.add(a[8]);
	v9.add(a[9]);
	v10.add(a[10]);
	v11.add(a[11]);
	v12.add(a[12]);
	v13.add(a[13]);
	v14.add(a[14]);
	v15.add(a[15]);

print v1
print v2
print v3
print v4
print v5
print v6
print v7
print v8
print v9
print v10
print v11
print v12
print v13
print v14
print v15


