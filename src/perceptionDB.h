// // CMakeProject1.h : Include file for standard system include files,
// // or project specific include files.

// #pragma once

// #include <iostream>
// #include <vector>
// #include <mutex>
// #include <shared_mutex>
// #include <optional>

// class PercetionResult
// {
// public:
// 	enum class Status 
// 	{
// 		Invalid,
// 		Valid,
// 		Retrieved,
// 	};
// 	using cPtr = std::shared_ptr<const PercetionResult>;
// 	PercetionResult() : _status(Status::Invalid)
// 	{
// 		_ptr = std::make_shared<PercetionResult>(this);
// 	}

// 	cPtr ptr() const { return std::static_pointer_cast<const PercetionResult>(_ptr); }
// 	void setVisionServiceName(const std::string& name) { _visionServiceName = name; }
// 	void setData(int data) { _data = data; }

// private:
// 	cPtr _ptr;
// 	std::string _visionServiceName;
// 	Status _status;
// 	int _data;
// };

// class PerceptionDB
// {
// public:
// 	using ExecuteID = int;
// 	struct Value {
// 		Value() = default;
// 		ExecuteID executeID;
// 		PercetionResult result;
// 	};
// 	void put(const ExecuteID& executeID, const PercetionResult& result)
// 	{
// 		std::unique_lock<std::shared_mutex> lock(_mutex);
// 		Value value;
// 		if (find(executeID, value))
// 			value.result = result;
// 		else
// 			_values.push_back({ executeID , result});
// 	}
// 	PercetionResult::cPtr get(const ExecuteID& executeID) const
// 	{
// 		std::shared_lock<std::shared_mutex> lock(_mutex);
// 		Value value;
// 		if (find(executeID, value))
// 			return value.result.ptr();
// 		return nullptr;
// 	}

// private:
// 	bool find(const ExecuteID& executeID, Value& value) const
// 	{
// 		for (const auto& v : _values)
// 		{
// 			if (v.executeID == executeID) {
// 				value = v;
// 				return true;;
// 			}
// 		}
// 		return false;
// 	}
// 	std::vector<Value> _values;
// 	mutable std::shared_mutex _mutex;
// };

// // TODO: Reference additional headers your program requires here.
