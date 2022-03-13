# CPP-Entry-Point
A simplistic implementation of a view class for command line arguments and associated substitute entry point
Regarding the discussion P0781 on IsoCPP standardization. IMHO The solution provided here has achieved the goal without modifying
the toolchain. A header-only library subjugating the two veiw classes 'std::span' and 'std::view' to reach the downto zero runtime overhead
as well as minimum exposure to bug.
This short library is trying to solve the unsafety of using command line arguments in main function once for good and all.
