#include "pch.h"
#include "Day7.h"

#include <fmt/core.h>
#include "Common/FileUtils.h"
#include "Common/StringUtils.h"
#include "Common/Timer.h"


namespace Day7
{
	std::pair<std::string, std::string> ParseCommandLine(const std::string& wholeLine)
	{
		const std::vector<std::string> parts = Common::StringUtils::Split(wholeLine, ' ');

		// The first part will contain '$', so we skip that

		return {
			parts[1],
			parts.size() > 2 ? parts[2] : ""
		};
	}


	void InitializeFileSystem(const std::vector<std::string>& lines, FileSystem& fs)
	{
		for (u32 i = 0; i < lines.size(); ++i)
		{
			const std::string& line = lines[i];

			if (!line.starts_with('$'))
			{
				continue;
			}

			const auto [command, params] = ParseCommandLine(line);

			if (command == "cd")
			{
				fs.ChangeDir(params);
				continue;
			}

			if (command == "ls")
			{
				for (++i; i < lines.size(); ++i)
				{
					// If the line is a command, we stop parsing files
					if (lines[i].starts_with("$"))
					{
						// Decrease i so that we can re-evaluate when we break out to the parent loop.
						--i;
						break;
					}

					const std::vector<std::string> lineParts = Common::StringUtils::Split(lines[i], ' ');
					if (lineParts[0] == "dir")
					{
						fs.CreateDirectory(lineParts[1]);
					}
					else
					{
						fs.CreateFile(lineParts[1], std::stoi(lineParts[0]));
					}
				}
			}
		}

		// Cache all the directory sizes.
		fs.GetHomedir()->CacheSize();
	}

	void AddDirectoryIfSizeThreshold(Directory& currentDir, std::vector<Directory*>& dirs, const u32 sizeThreshold)
	{
		if (currentDir.cachedSize <= sizeThreshold)
		{
			dirs.push_back(&currentDir);
		}

		for (Directory& dir : currentDir.directories)
		{
			AddDirectoryIfSizeThreshold(dir, dirs, sizeThreshold);
		}
	}

	void Flatten(Directory* dir, std::vector<Directory*>& directories)
	{
		std::vector<Directory*> dirs{};

		for (u32 i = 0; i < dir->directories.size(); ++i)
		{
			directories.push_back(&dir->directories[i]);
			Flatten(&dir->directories[i], directories);
		}
	}

	void Run()
	{
		fmt::print("=====[ AdventOfCode Day 7 ]=====\n");

		std::vector<std::string> lines{};
		Common::ReadFileSync("src/Puzzles/Day07/input.txt", lines);

		// Parse the filesystem from the input.
		FileSystem fs;
		InitializeFileSystem(lines, fs);


		fmt::print("\n-----[ Part 1 ]-----\n");

		{
			std::vector<Directory*> directories{};
			u32 totalSize = 0;

			AddDirectoryIfSizeThreshold(*fs.GetHomedir(), directories, 100'000);

			for (const Directory* dir : directories)
			{
				totalSize += dir->cachedSize;
			}

			fmt::print("The size of all directories smaller than 100000 combined is {}\n", totalSize);
		}


		fmt::print("\n-----[ Part 2 ]-----\n");

		{
			u32 usedSpace = fs.GetHomedir()->cachedSize;
			u32 freeSpace = 70'000'000 - usedSpace;
			u32 minimumRequiredSpace = 30'000'000 - freeSpace;

			fmt::print("Used space: {} - free space: {} - minimum space to clear up: {}\n", usedSpace, freeSpace, minimumRequiredSpace);

			std::vector<Directory*> dirs{};
			Flatten(fs.GetHomedir(), dirs);

			std::sort(dirs.begin(), dirs.end(), [](Directory* a, Directory* b)
			{
				return a->cachedSize < b->cachedSize;
			});

			for (auto dir : dirs)
			{
				if (dir->cachedSize >= minimumRequiredSpace)
				{
					fmt::print("The directory that we need to delete is {} - freeing up {} space\n", dir->name, dir->cachedSize);
					break;
				}
			}
		}
	}

	void Directory::CacheSize()
	{
		cachedSize = 0;

		for (const File& file : files)
		{
			cachedSize += file.size;
		}

		for (Directory& dir : directories)
		{
			dir.CacheSize();
			cachedSize += dir.cachedSize;
		}
	}

	FileSystem::FileSystem()
	{
		m_HomeDir = Directory{
			.name = "/",
			.parentDir = nullptr,
			.files = {},
			.directories = {}
		};
		m_CurrentDir = &m_HomeDir;
	}

	void FileSystem::ChangeDir(const std::string& dirName)
	{
		if (dirName == "/")
		{
			m_CurrentDir = &m_HomeDir;
			return;
		}

		if (dirName == "..")
		{
			m_CurrentDir = m_CurrentDir->parentDir;
			return;
		}

		const auto result = std::ranges::find_if(m_CurrentDir->directories, [&](const Directory& dir)
		{
			return dir.name == dirName;
		});

		if (result == m_CurrentDir->directories.end())
		{
			return;
		}

		m_CurrentDir = &*result;
	}

	void FileSystem::CreateDirectory(const std::string& name)
	{
		// First check if the directory already exists.
		const auto result = std::ranges::find_if(m_CurrentDir->directories, [&](const Directory& dir)
		{
			return dir.name == name;
		});

		if (result != m_CurrentDir->directories.end())
		{
			throw std::runtime_error("Cannot create directory, it already exists.");
		}

		m_CurrentDir->directories.push_back({ name, 0, m_CurrentDir, {}, {} });
	}

	void FileSystem::CreateFile(const std::string& name, u32 size)
	{
		// First check if the file already exists.
		const auto result = std::ranges::find_if(m_CurrentDir->files, [&](const File& file)
		{
			return file.name == name;
		});

		if (result != m_CurrentDir->files.end())
		{
			throw std::runtime_error("Cannot create file, it already exists.");
		}

		m_CurrentDir->files.push_back({ size, name });
	}
}
