#ifndef __MOSDRGPEERNOTIFY_H
#define __MOSDRGPEERNOTIFY_H

#include "msg/Message.h"


class MOSDRGNotify : public Message {
  __uint64_t       map_version;
  list<repgroup_t> rg_list;

 public:
  __uint64_t get_version() { return map_version; }
  list<repgroup_t>& get_rg_list() { return rg_list; }

  MOSDRGNotify() {}
  MOSDRGNotify(__uint64_t v, list<repgroup_t>& l) :
	Message(MSG_OSD_RG_NOTIFY) {
	this->map_version = v;
	rg_list.splice(rg_list.begin(), l);
  }
  
  char *get_type_name() { return "RGnot"; }

  void encode_payload() {
	payload.append((char*)&map_version, sizeof(map_version));
	_encode(rg_list, payload);
  }
  void decode_payload() {
	int off = 0;
	payload.copy(off, sizeof(map_version), (char*)&map_version);
	off += sizeof(map_version);
	_decode(rg_list, payload, off);
  }
};

#endif
