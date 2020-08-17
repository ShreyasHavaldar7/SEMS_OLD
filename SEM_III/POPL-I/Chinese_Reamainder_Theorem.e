note
	description: "Chinese Remainder Theorem"
	author: "Shreyas Jayant Havaldar"

class
	CS18BTECH11042
			-- Chinese Remainder Class

create
	make

feature
	No: INTEGER
			-- Product of n[i] for all i from 1 to k
    n: ARRAY[INTEGER]
			-- Integers as divisors input by the user. Should be greater than 1
	a: ARRAY[INTEGER]
			-- Remainders input by the user. a[i] < n[i] for all i.
	k: INTEGER
			-- Total no of divisors.
	ch: BOOLEAN
			-- Check if condition satisfied


feature --File Access

	in_file: PLAIN_TEXT_FILE
	out_file: PLAIN_TEXT_FILE

feature
		make

			local
				res:INTEGER

			do

				create in_file.make_open_read("input.txt") -- Create a file object and opening as read only
				create out_file.make_open_write ("output.txt")

				inp
				res:=find
				out_file.put_integer (res)
				out_file.put_new_line
				out_file.close
			end



		inp -- Reading necessary values from input file

			local
				i: INTEGER
				j: INTEGER
			    p: INTEGER
			    q: INTEGER
			    X: INTEGER


			do
				No:=1

				in_file.read_word
				k:= in_file.last_string.to_integer
				create n.make_filled(0,1,k)
				create a.make_filled(0,1,k)

					from
							i:=1
					invariant
							bound: i>0 and i<=k+1
					until
							i > k
					loop
							in_file.read_word
							p:=in_file.last_string.to_integer
							n[i] := p
							No:=No*n[i] -- Calculating the product of all divisors

							in_file.read_word
							q := in_file.last_string.to_integer
							a[i]:=q

							i:=i+1

					end

				ensure -- Checking if all necessary conditions satisfied
					checking: checks=True
					non_empty: k>0

				rescue
					out_file.put_string ("INVALID")
					out_file.put_new_line
					out_file.close

			end

		checks: BOOLEAN

			require
				non_empty: k>0

			local
				i:INTEGER

			do
				Result:= True
				from i:=1
				until i>k
				loop
				if (a[i]<0 or n[i]<=1 or n[i]<=a[i])  then
					-- Checking pre-required conditions are satisfied
					Result:=False
				end
				if (coprime(((No/n[i]).truncated_to_integer), n[i]) = False) then
					-- Checking if the two numbers are co-prime
					Result:=False
				end
				i:=i+1
				end
			end

		inverse_mod(l: INTEGER; b: INTEGER): INTEGER
			-- Calculates the inverse modulo

			require
				 checking: checks=TRUE
				 non_empty: k>0

			local
				u,v,w,x,y,z : INTEGER

			do
				w:=b
				x:=0
				y:=1

				if b=1 then
					Result:= 0

				else
					from z:= l
					until z<=1
					loop
						u := (z/w).truncated_to_integer
						v := w
						w := z \\ w
						z := v
						v := x
						x := y - u*x
						y := v

					end

					if y<0 then
						y := y + b
					end

					Result:= y
				end

			ensure
				checking: checks=True

			rescue
				out_file.put_string ("INVALID")
				out_file.put_new_line
				out_file.close
			end

		find:INTEGER
			-- Finding the no by using Chinese Remainder Theorem

			require
				 checking: checks=TRUE
				 non_empty: k>0

			local
				i, pp, res : INTEGER

			do
				from i:=1
				invariant
					i<=k+1
				until i>k
				loop

					i:= i+1
				end

				res:=0

				from i:=1
				invariant
					i<=k+1
				until i>k
				loop
					pp:= (No/n[i]).truncated_to_integer
					res:= res + a[i] * inverse_mod(pp, n[i]) * pp
					i:= i+1
				end
				Result:= res \\ No



			ensure
				checking: checks=True
				Result_satisfies: correctness(Result) = True
				smallest_X: smallest_correct(Result)=True

			rescue
				out_file.put_string ("INVALID")
				out_file.put_new_line
				out_file.close

			end

		correctness(X: INTEGER): BOOLEAN
			--Verifying that the answer obtained is correct

			require
				non_zero: X>0
			local
				i:INTEGER

			do
				Result:= True
				from i:=1
				invariant bounds: i>0 and i<=k+1
				until i>k
				loop
					if ((X \\ n[i]) /= a[i]) then
						Result:= False

					end
				i:=i+1
				end
			end

		smallest_correct(X: INTEGER): BOOLEAN --Checking that the no calculated is the smallest satisfying the required values

			require
				non_zero: X>0
			local
				i:INTEGER

			do
				Result:= True
				from i:=1
				until i>=X
				loop
					if(correctness(i)=True) then
						Result:=False
					end
				i:=i+1
				end
			end


		gcd(m1: INTEGER; m2: INTEGER): INTEGER
			--Calculating the gcd of m1 and m2

			require
				 checking: checks=TRUE
				 non_empty: k>0

			do

				if m2=0 then
					Result:= m1
				else
				Result:= gcd(m2, m1 \\ m2)
				end
			ensure
				checking: checks=True

			rescue
				out_file.put_string ("INVALID")
				out_file.put_new_line
				out_file.close
			end

		coprime(n1:INTEGER; n2:INTEGER): BOOLEAN
			-- To check if two numbers are co-prime
			require
				checking: checks=TRUE
				non_empty: k>0

			do
				if gcd(n1,n2)=1 then
					Result:= TRUE
				else
					Result:= False
				end

			ensure
				checking: checks=True

			rescue
				out_file.put_string ("INVALID")
				out_file.put_new_line
				out_file.close
			end


end
