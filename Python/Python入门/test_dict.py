scores = {'小明': 95}
print(scores)

#打印某个key对应的value
print(scores['小明'])

#添加元素
# scores['小美'] = 99
# print(scores)
scores.update({'小美': 99})
print(scores)

del scores['小美']
print(scores)

li = [11, 22, 33]
a = dict(enumerate(li, 10)) #给列表每一项添加序号，然后初始化字典
print(a)

a = {"k1": 123}
a["k2"] = 456
print(a)

for k in a.keys():
    print(k)

for v in a.values():
    print(v)

for k, v in a.items():
    print(k, ":", v)
