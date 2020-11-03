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

module Peaks

import Statistics
export findPeaks

# Defines a point. X values are integers. Y values are floating point.
mutable struct GraphPoint
    x::UInt
    y::Float64
end

# List of points.
#struct GraphLine <: Array{GraphPoint} end

# Defines a peak. A peak is described by three points: a left trough, a peak, and a right trough.
mutable struct GraphPeak
    leftTrough::GraphPoint
    peak::GraphPoint
    rightTrough::GraphPoint
    area::Float64
end

# List of points.
#struct GraphPeakList <: Array{GraphPeak} end

function computeArea(data, currentPeak::GraphPeak)
    currentPeak.area = 0.0
    
    if currentPeak.leftTrough.x < currentPeak.rightTrough.x
        for i in currentPeak.leftTrough.x+1:currentPeak.rightTrough.x
            b = data[i] + data[i - 1]
            currentPeak.area += (0.5 * b)
        end
    end
end

# Returns a list of all statistically significant peaks in the given waveform.
# These are defined as peaks that rise more than one standard deviation above the mean for at least three points on the x axis.

function findPeaks(data::Array{Float64}, sigmas = 1.0)
    peaks = []

    mean = Statistics.mean(data)
    stddev = sigmas * Statistics.std(data)
    threshold = mean + stddev
    currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)
    x = 1

    for y in data

        if y < threshold

            # Have we found a peak? If so, add it and start looking for the next one.
            if currentPeak.rightTrough.x > 0
                computeArea(data, currentPeak)
                push!(peaks, currentPeak)
                currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)

            # Are we looking for a left trough?
            elseif currentPeak.leftTrough.x == 0
                currentPeak.leftTrough.x = x
                currentPeak.leftTrough.y = y

            # If we have a left trough and an existing peak, assume this is the right trough - for now.
            elseif (currentPeak.peak.x > currentPeak.leftTrough.x) && (currentPeak.leftTrough.x > 0)
                currentPeak.rightTrough.x = x
                currentPeak.rightTrough.y = y

            else
                currentPeak.leftTrough.x = x
                currentPeak.leftTrough.y = y
            end

        elseif currentPeak.leftTrough.x > 0 # Left trough is set.

            # Are we looking for a peak or is this bigger than the current peak?
            if currentPeak.peak.x == 0 || y >= currentPeak.peak.y
                currentPeak.peak.x = x
                currentPeak.peak.y = y
            end

        elseif currentPeak.rightTrough.x > 0 # Right trough is set.
            computeArea(data, currentPeak)
            push!(peaks, currentPeak)
            currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)

        else # Nothing is set, but the value is above the threshold.
            currentPeak.leftTrough.x = x
            currentPeak.leftTrough.y = y
        end

        x = x + 1
    end

    peaks
end

function average(data::Array{GraphPoint})
    sum = 0.0

    for item in data
        sum = sum + item.y
    end

    avg = sum / length(data)
    avg
end

function variance(data::Array{GraphPoint}, mean)
    numerator = 0.0

    for item in data
        numerator = numerator + ((item.y - mean) * (item.y - mean))
    end

    variance = numerator / length(data)
    variance
end

function standardDeviation(data::Array{GraphPoint}, mean)
    var = variance(data, mean)
    dev = sqrt(var)
    dev
end

function findPeaks(data::Array{GraphPoint}, sigmas = 1.0)
    peaks = []

    mean = average(data)
    stddev = sigmas * standardDeviation(data, mean)
    threshold = mean + stddev
    currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)
    x = 1

    for point in data

        if point.y < threshold

            # Have we found a peak? If so, add it and start looking for the next one.
            if currentPeak.rightTrough.x > 0
                computeArea(data, currentPeak)
                push!(peaks, currentPeak)
                currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)

            # Are we looking for a left trough?
            elseif currentPeak.leftTrough.x == 0
                currentPeak.leftTrough = point

            # If we have a left trough and an existing peak, assume this is the right trough - for now.
            elseif (currentPeak.peak.x > currentPeak.leftTrough.x) && (currentPeak.leftTrough.x > 0)
                currentPeak.rightTrough = point

            else
                currentPeak.leftTrough = point
            end

        elseif currentPeak.leftTrough.x > 0 # Left trough is set.

            # Are we looking for a peak or is this bigger than the current peak?
            if currentPeak.peak.x == 0 || y >= currentPeak.peak.y
                currentPeak.peak = point
            end

        elseif currentPeak.rightTrough.x > 0 # Right trough is set.
            computeArea(data, currentPeak)
            push!(peaks, currentPeak)
            currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)

        else # Nothing is set, but the value is above the threshold.
            currentPeak.leftTrough = point
        end

        x = x + 1
    end

    peaks
end

function findPeaksOfSize(data::Array{GraphPoint}, minPeakArea, sigmas = 1.0)
    peaks = []

    mean = average(data)
    stddev = sigmas * standardDeviation(data, mean)
    threshold = mean + stddev
    currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)
    x = 1

    for point in data

        if point.y < threshold

            # Have we found a peak? If so, add it and start looking for the next one.
            if currentPeak.rightTrough.x > 0
                computeArea(data, currentPeak)
                if currentPeak.area >= minPeakArea
                    push!(peaks, currentPeak)
                end
                currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)

            # Are we looking for a left trough?
            elseif currentPeak.leftTrough.x == 0
                currentPeak.leftTrough = point

            # If we have a left trough and an existing peak, assume this is the right trough - for now.
            elseif (currentPeak.peak.x > currentPeak.leftTrough.x) && (currentPeak.leftTrough.x > 0)
                currentPeak.rightTrough = point

            else
                currentPeak.leftTrough = point
            end

        elseif currentPeak.leftTrough.x > 0 # Left trough is set.

            # Are we looking for a peak or is this bigger than the current peak?
            if currentPeak.peak.x == 0 || y >= currentPeak.peak.y
                currentPeak.peak = point
            end

        elseif currentPeak.rightTrough.x > 0 # Right trough is set.
            computeArea(data, currentPeak)
            if currentPeak.area >= minPeakArea
                push!(peaks, currentPeak)
            end
            currentPeak = GraphPeak(GraphPoint(0,0.0), GraphPoint(0,0.0), GraphPoint(0,0.0), 0.0)

        else # Nothing is set, but the value is above the threshold.
            currentPeak.leftTrough = point
        end

        x = x + 1
    end

    peaks
end

end
