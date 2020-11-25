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

module Distance

export hamming_distance
export levenshtein_distance
export euclidian_distance_1D
export euclidian_distance_2D

# Hamming Distance
function hamming_distance(str1, str2)
	len1 = length(str1)

	# The strings must be the same length.
	if len1 != length(str2)
		return -1
    end

	distance = 0

    for i in 1:len1
		if str1[i] != str2[i]
			distance = distance + 1
        end
    end

	distance
end

# Levenshtein Distance
function levenshtein_distance(str1, str2)
	m = length(str1)
	n = length(str2)

	# Test for empty strings.
	if m == 0
		return n
    end
	if n == 0
		return m
    end

	# Temp vectors.
	v0 = zeros(n)
	v1 = zeros(n)
    for i in 1:n
		v0[i] = i - 1
    end

    for i in 1:m - 1
		v1[1] = i + 1
		
        for j in 1:n - 1
            costs = zeros(3) # deletion, insertion, and substitution costs (in that order)
			costs[1] = v0[j + 1] + 1
			costs[2] = v1[j] + 1
			if str1[i] == str2[j]
				costs[3] = v0[j]
			else
				costs[3] = v0[j] + 1
            end

            tempJ = j + 1
			v1[tempJ] = costs[1]
            if costs[2] < v1[tempJ]
                v1[tempJ] = costs[2]
            end
            if costs[3] < v1[tempJ]
                v1[tempJ] = costs[3]
            end
		end
		
		# Copy v1 to v0.
        tempV = v0
        v0 = v1
        v1 = tempV
    end

	# Save the final distance calculation.
	distance = v0[n]

	distance
end

# 1 dimensional Euclidian distance
function euclidian_distance_1D(pt1, pt2)
	abs(pt1 - pt2)
end

# 2 dimensional Euclidian distance
function euclidian_distance_2D(pt1X, pt1Y, pt2X, pt2Y)
	tempX = pt2X - pt1X
	tempY = pt2Y - pt1Y
	sqrt((tempX * tempX) + (tempY * tempY))
end

end
