#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

string vec_to_string(vector<string> vec) {
  ostringstream oss;

  if (!vec.empty())
  {

    // Convert all but the last element to avoid a trailing ","
    copy(vec.begin(), vec.end()-1,
        ostream_iterator<string>(oss, " "));

    // Now add the last element with no delimiter
    oss << vec.back();
  }

  return oss.str();
}

void remove_at(std::vector<string>& v, typename std::vector<string>::size_type n)
{
    std::swap(v[n], v.back());
    v.pop_back();
}

static void show_usage(std::string name)
{
    std::cerr << "Usage: " << name << " INPUT_FILE [SIZE]"
              << std::endl;
}

int main(int argc, char* argv[]) {
    srand(time(0));

    int size = 365;
    int delId;


    if (argc < 2) {
        show_usage(argv[0]);
        return 1;
    }

    // Read file 
    ifstream ifs(argv[1]);
    if ( !ifs.is_open() ) {
        std::cerr << "Cannot open file" << endl;
        return 2;
    }

    if ( argc == 3 ) {
        size = std::stoi(argv[2]);
    }
    string content( (istreambuf_iterator<char>(ifs) ),
                    (istreambuf_iterator<char>()    ) );

    istringstream iss(content);
    cout << content.size() << endl;
    vector<string> tokens;

    copy(istream_iterator<string>(iss),
             istream_iterator<string>(),
             back_inserter< vector<string> >(tokens));

    while ( vec_to_string(tokens).size() > size ) {
        delId = rand() % tokens.size();
        remove_at(tokens, delId);
    }

    ofstream ofs("out.txt");
    ofs << vec_to_string(tokens);
    ofs.close();
    return 0;
}

