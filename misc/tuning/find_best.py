min_e = 100
best_adj = 10
best_bias = 10
for adj in range(4):
    for bias in range(17):
        f = 460.649 + (3.44283)*adj + (-4.40594)*bias
        e = abs(434.8 - f)
        print "adj={0}, bias={1}, e={2}".format(adj, bias, e)
        if e < min_e:
            print "new best"
            min_e = e
            best_adj = adj
            best_bias = bias
            min_e = e
print "ajd={0}, bias={1} giving error={2}".format(best_adj, best_bias, min_e)
