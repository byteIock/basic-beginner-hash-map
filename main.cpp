#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

template<std::size_t hash_size, typename t = const char*>
requires std::is_same_v<t, const char*>
class hash_table {
private:
	std::vector<const char*> values;
	std::map<const char*, int> recycle;
	std::vector<std::string> message_logs;
	void* hash_buffer = nullptr;
	int x = 0;
public:
	hash_table() {hash_buffer = static_cast<void*>(malloc(sizeof(hash_size)));}
	~hash_table() {free(hash_buffer);}

	bool remove(const char* key) {
		for (auto it = values.begin(); it != values.end(); ++it) {
			if (_strcmpi(*it, key) == 0) {
				recycle[key] = x;
				values.erase(std::remove(values.begin(), values.end(), *it), values.end());
				x = 0;
				return true;

			}
			++x;
		}
		char message[256];
		sprintf_s(message, sizeof(message), "[+] couldn't retrieve [%s] from the hash table to remove", key);
		message_logs.push_back(message);
	};

	void display_log() {
		for (const auto& e : message_logs) {
			std::cout << e << "\n";
		};

		if (message_logs.capacity() <= 0) {
			std::cout << "[+] there's no elements in message logs";
		}
	};
	 
	const char* find(const char* key) {
		for (auto it = values.begin(); it != values.end(); ++it) {
			if (it == key) {
				return it;
			}
		}

		char msg[256];
		sprintf_s(msg, sizeof(msg), "[+] couldn't find [%c] within the hash table", key);
		message_logs.push_back(msg);
		return msg;
	}
	
	void display() {
		for (const auto& key : values) {
			std::cout << key << "\n";
		};
		if(values.capacity() <= 0) message_logs.push_back("[+] couldn't display hash there's no elements within");
	}

	void erase() {
		for (auto it = values.begin(); it != values.end(); ++it) {
			recycle[*it] = x;
			++x;
		}
		values.clear();
	};

	void restore() {
		for (auto it = recycle.begin(); it != recycle.end(); ++it) {
			values.push_back(it->first);
		};
		if (recycle.size() <= 0) message_logs.push_back("[+] there's no elements within recyle");
	};
	
	bool return_recyle(const char* key) {
		for (auto it = recycle.begin(); it != recycle.end(); ++it) {
			if (it->first == key) {
				values.push_back(it->first);
				return true;
			}
		}
		char message[256];
		sprintf_s(message, sizeof(message), "[+] couldn't find [%c] in the recyle bin to bring back", key);
		message_logs.push_back(message);
		return false;
	}

	void add(const char* key) {
		values.push_back(key);
	}

	
};  
 
int main() {
	hash_table<0x1000, const char*> hash;
}  
