#pragma once
#ifndef mirai_cpp_defs_temp_message_hpp_H_
#define mirai_cpp_defs_temp_message_hpp_H_

#include <nlohmann/json.hpp>
#include "qq_types.hpp"
#include "serializable.hpp"
#include "message_chain.hpp"
#include "group_member.hpp"

namespace Cyan
{
	// 由群组发来的临时消息
	class TempMessage : public Serializable
	{
	public:
		Cyan::MessageChain MessageChain;
		GroupMember_t Sender;

		TempMessage() = default;
		TempMessage(const TempMessage& gm)
		{
			MessageChain = gm.MessageChain;
			Sender = gm.Sender;
		}
		TempMessage& operator=(const TempMessage& t)
		{
			TempMessage tmp(t);
			std::swap(this->MessageChain, tmp.MessageChain);
			std::swap(this->Sender, tmp.Sender);
			return *this;
		}
		MessageId GetMessageId() const
		{
			return (this->MessageChain).GetMessageId();
		}

		int64_t GetTimestamp() const
		{
			return (this->MessageChain).GetTimestamp();
		}
		virtual ~TempMessage() = default;
		virtual bool Set(const json& j) override
		{
			this->MessageChain.Set(j["messageChain"]);
			Sender.Set(j["sender"]);
			return true;
		}
		virtual json ToJson() const override
		{
			json j = json::object();
			j["messageChain"] = this->MessageChain.ToJson();
			j["sender"] = this->Sender.ToJson();
			return j;
		}
	};
}

#endif // !mirai_cpp_defs_temp_message_hpp_H_