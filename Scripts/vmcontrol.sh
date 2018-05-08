#!/bin/bash
#Description: VM Power Control Script

#Global Print Confirm Message Flag
g_confirm_flag=""
g_answer=""

confirm() {
  if [ "${g_confirm_flag}"x = "1"x ]; then
    g_answer="1"
  else
    echo "$1"
    read g_answer
  fi
}

vmcontrol_power_on() {
  for f in $(VBoxManage list vms | awk -F\" '{print $2}'); do
    confirm "Power on ${f}?(y/n):";
    if [ "${g_answer}"x = "y"x -o "${g_answer}"x = "1"x ]; then
      VBoxManage startvm "$f" --type headless
    fi
  done

  for f in $(VBoxManage list runningvms | awk -F\" '{print $2}'); do
    VBoxManage guestproperty wait "$f" /VirtualBox/GuestInfo/Net/0/V4/IP --timeout 60000
    t=$(VBoxManage guestproperty get "$f" /VirtualBox/GuestInfo/OS/Product)
      echo "$f OS {$t} Property (IP):"
      VBoxManage guestproperty enumerate "$f" | grep IP
  done
}

vmcontrol_power_off() {
  for f in $(VBoxManage list runningvms | awk -F\" '{print $2}'); do
    confirm "Power off ${f}?(y/n):"
    if [ "${g_answer}"x = "y"x -o "${g_answer}"x = "1"x ]; then
      VBoxManage controlvm "$f" poweroff
    fi
  done
}




#VMControl Script Begin
if [ "${1}"x = "-f"x -o "${2}"x = "-f"x ]; then 
  g_confirm_flag="1"
else
  g_confirm_flag="0"
fi

power_mod="poweron"
if [ "${1}"x = "poweroff"x -o "${2}"x = "poweroff"x ]; then 
  power_mod="poweroff"
fi

case $power_mod in 
  "poweron")
     vmcontrol_power_on
  ;;
  "poweroff")
     vmcontrol_power_off
  ;;
esac
#VMControl Script End 
