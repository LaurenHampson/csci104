// operator overload to make printing all text in a webpage easier
	  	// called when you want to display text in search
		std::ostream& operator<< (std:: ostream& os, const WebPage &wp)
		{
			std::ifstream input(wp.filename_); // create input stream from the webpage passed in by the user
			if (!input.is_open())//check if the weeb page exists
			{
				throw std::logic_error ("invalid web page");// error thrown if the web page does not exist
			}

			std::string output = ""; // new string
			std::queue<std::string> str;
			char c; // character to read in single characters from input file

			while (input.get(c))// loops through getting single characters
			{
				//cq.push(d);
				if (isalpha(c))
				{
					output += c;
				}
				else if (output != "")
				{
					str.push(output);
					output = "";
				}	
				if (c == '[')//makes sure to read in what is in the brackets excluding the file name
				{
					std::string textDescription = "";

					std::queue<char> cq;

					bool description = false;
					bool link = false;

					char d;

					while(input.get(d))
					{
						//cq.push(d);
						if (isalpha(d))
						{
							textDescription += d;
						}
						else if (output != "")
						{
							str.push(textDescription);
							textDescription = "";
						}
						if (d == ']')
						{
							description = true;
							break;
						}
						textDescription += d;

					}
					//if (input.get(d))
					//{
					//	cq.push(d);
					//}
					
						if (d == '(')
						{
							while (input.get(d))
							{
								if (d == ')')
								{
									link = true;
									break;
								}

								if (d == ' ')
								{
									break;
								}
							}
						}

					if (link && description)
					{
						output += "[" + textDescription + "]";
						str.push(output);
					}
					/*else
					{
						while (!cq.empty())
						{
							char x = cq.front();
							output+= x;
							cq.pop();
						}
					}*/

				}
			
				/*else// adds all other characters to the output string
				{
					output+= c; // add the characters to the output file
				}*/

			}
			
			str.push(output);

			for (unsigned int i = 0; i < str.size(); i++)
			{
				os << str.front() << " ";
				str.pop();
			}
			os << std::endl;
			//os << output; // overiding so it prints all contents of the webpage
			input.close(); // closes the input file
			return os;
		}
