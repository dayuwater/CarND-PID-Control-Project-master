# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.pid.Debug:
/Users/tanwang/Downloads/CarND-PID-Control-Project-master/Debug/pid:
	/bin/rm -f /Users/tanwang/Downloads/CarND-PID-Control-Project-master/Debug/pid


PostBuild.pid.Release:
/Users/tanwang/Downloads/CarND-PID-Control-Project-master/Release/pid:
	/bin/rm -f /Users/tanwang/Downloads/CarND-PID-Control-Project-master/Release/pid


PostBuild.pid.MinSizeRel:
/Users/tanwang/Downloads/CarND-PID-Control-Project-master/MinSizeRel/pid:
	/bin/rm -f /Users/tanwang/Downloads/CarND-PID-Control-Project-master/MinSizeRel/pid


PostBuild.pid.RelWithDebInfo:
/Users/tanwang/Downloads/CarND-PID-Control-Project-master/RelWithDebInfo/pid:
	/bin/rm -f /Users/tanwang/Downloads/CarND-PID-Control-Project-master/RelWithDebInfo/pid




# For each target create a dummy ruleso the target does not have to exist
