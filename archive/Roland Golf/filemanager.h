struct filemanager
{
	ifstream infile;
	std::string data;
	std::vector<string> datafile;
	std::vector<string> open(std::string filename)
	{
		infile.open(filename.c_str());
		infile.seekg(0,ifstream::end);
		size = infile.tellg();
		infile.seekg(0);
		int temp = 0;
		while(!infile.eof())
		{
			getline(infile,data);
			datafile.push_back(data);
			temp++;
		}
		return datafile;
	};
};