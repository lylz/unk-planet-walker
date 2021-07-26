#pragma once

class IdentifierManager
{
public:
	static IdentifierManager &GetInstance()
	{
		static IdentifierManager instance;

		return instance;
	}

	int GetNewIdentifier()
	{
		return ++identifier_;
	}

	IdentifierManager(IdentifierManager const &) = delete;
	void operator=(IdentifierManager const &) = delete;

private:
	IdentifierManager()
	{
		identifier_ = 0;
	};

private:

	int identifier_;
};
