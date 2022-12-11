#pragma once

namespace Day7
{
	void Run();

	struct File
	{
		u32 size;
		std::string name;
	};

	struct Directory
	{
		std::string name;
		u32 cachedSize = 0;
		Directory* parentDir = nullptr;
		std::vector<File> files;
		std::vector<Directory> directories;

		void CacheSize();
	};

	class FileSystem
	{
	public:
		FileSystem();

		void ChangeDir(const std::string& dirName);

		void CreateDirectory(const std::string& name);
		void CreateFile(const std::string& name, u32 size);

		Directory* GetHomedir() { return &m_HomeDir; }

	private:
		Directory m_HomeDir;
		Directory* m_CurrentDir;
	};
}
