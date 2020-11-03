#	MIT License
#
#  Copyright © 2020 Michael J Simms. All rights reserved.
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy
#	of this software and associated documentation files (the "Software"), to deal
#	in the Software without restriction, including without limitation the rights
#	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#	copies of the Software, and to permit persons to whom the Software is
#	furnished to do so, subject to the following conditions:
#
#	The above copyright notice and this permission notice shall be included in all
#	copies or substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#	SOFTWARE.

include("Distance.jl")
include("Peaks.jl")
include("Powers.jl")
include("Signals.jl")

using Pkg
Pkg.add("ArgParse")
using ArgParse
Pkg.add("CSV")
using CSV

function readAccelerometerCsv(fileName::String)
    data = []
    data = CSV.read(fileName)
    ts = data[1]
    x = data[2]
    y = data[3]
    z = data[4]
    ts, x, y, z
end

function distanceTests()
	println("Distance Tests:")
	println("---------------")

	distance = Distance.hammingDistance("1011101", "1001001")
	println("Hamming Distance: ", distance)
	@assert distance == 2

	distance = Distance.levenshteinDistance("foo", "foobar")
	println("Levenshtein Distance: ", distance)
	@assert distance == 3
end

function signalsTests()
	println("Signals Tests:");
	println("--------------");

	inData = [ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 ]
    windowSize = 2
    outData = Signals.smooth(inData, windowSize)
	
    println(outData)
end

function powerTests()
	println("Power Tests:")
	println("------------")

	nearest = Powers.NearestPowerOf2(63)
	println("Nearest power of 2 for 63 is ", nearest)
	@assert nearest == 64
end

function peakFindingTests(data)
	println("Peak Finding Tests:")
	println("-------------------")

    peaks = Peaks.findPeaks(data)
    println(peaks)
end

# Parses the command line arguments
function parse_commandline()
    s = ArgParseSettings()

    @add_arg_table s begin
        "--csv"
            help = "another option with an argument"
            arg_type = String
            default = "data/10_pullups.csv"
    end

    return parse_args(s)
end

# Run all the unit tests
parsed_args = parse_commandline()
ts, x, y, z = readAccelerometerCsv(parsed_args["csv"])
distanceTests()
println("")
signalsTests()
println("")
powerTests()
println("")
peakFindingTests(x)
println("")
