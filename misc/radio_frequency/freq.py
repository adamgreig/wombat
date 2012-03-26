def freq(khz):
    khz = int(khz)
    f_pfd = 24576;
    n = int(khz*10 / f_pfd);
    m = int(((((khz*10000)/f_pfd) - (n*1000)) * 4096)/1000)
    f = f_pfd/10 * (n + (m/4096.0))
    print "n: {n}, m: {m}, f: {f}".format(n=n, m=m, f=f)

freq(434000)
