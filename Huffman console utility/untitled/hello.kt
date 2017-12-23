import platform.posix.clock

const val MAX_N = 10_000_000


fun main(args: Array<String>) {
    var time = clock()
    var s = 0L
    for (i in (0..MAX_N)) {
        if (i % 3 == 2) {
            s += i * i
        }
    }
    println("simple loop :\ntime : ${(clock() - time) / 1000000.0} sec.")
//    time = clock()
//    s = (0..MAX_N)
//            .filter { it % 3 == 2 }
//            .map { it * it.toLong() }
//            .sum()
//    println("kotlin lib:\ntime : ${(clock() - time)  / 1000000.0} sec.")
    time = clock()
    s = (0..MAX_N)
            .asSequence()
            .filter { it % 3 == 2 }
            .map { (it * it).toLong() }
            .sum()
    println("kotlin lib + asSequence() optimize:\ntime : ${(clock() - time) / 1000000.0} sec.")
}